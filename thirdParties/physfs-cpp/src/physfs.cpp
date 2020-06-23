#include "physfs.hpp"

#include <streambuf>
#include <string>
#include <string.h>
#include <stdexcept>

using std::streambuf;
using std::ios_base;

namespace PhysFS
{
	class fbuf : public streambuf
	{
	private:
		int_type underflow() override
		{
			if (PHYSFS_eof(file)) {
				return traits_type::eof();
			}

			sint64 bytesRead  = PHYSFS_readBytes(file, buffer, bufferSize);

			if (bytesRead < 1) {
				return traits_type::eof();
			}

			setg(buffer, buffer, buffer + bytesRead);

			return (unsigned char) *gptr();
		}

		pos_type seekoff(off_type pos, ios_base::seekdir dir, ios_base::openmode mode) override
		{
			switch (dir)
			{
				case std::ios_base::beg:
					PHYSFS_seek(file, pos);
					break;
				case std::ios_base::cur:
					// subtract characters currently in buffer from seek position
					PHYSFS_seek(file, (PHYSFS_tell(file) + pos) - (egptr() - gptr()));
					break;
				case std::ios_base::end:
					PHYSFS_seek(file, PHYSFS_fileLength(file) + pos);
					break;
			}

			if (mode & std::ios_base::in) {
				setg(egptr(), egptr(), egptr());
			}

			if (mode & std::ios_base::out) {
				setp(buffer, buffer);
			}

			return PHYSFS_tell(file);
		}

		pos_type seekpos(pos_type pos, std::ios_base::openmode mode) override
		{
			PHYSFS_seek(file, pos);
			if (mode & std::ios_base::in) {
				setg(egptr(), egptr(), egptr());
			}
			if (mode & std::ios_base::out) {
				setp(buffer, buffer);
			}
			return PHYSFS_tell(file);
		}

		int_type overflow( int_type c ) override
		{
			if (pptr() == pbase() && c == traits_type::eof()) {
				return 0; // no-op
			}

			if (PHYSFS_writeBytes(file, pbase(), pptr() - pbase()) < 1) {
				return traits_type::eof();
			}

			if (c != traits_type::eof()) {
				if (PHYSFS_writeBytes(file, &c, 1) < 1) {
					return traits_type::eof();
				}
			}

			return 0;
		}

		int sync() override
		{
			return overflow(traits_type::eof());
		}

		char * buffer;
		size_t const bufferSize;

	protected:
		PHYSFS_File * const file;

	public:
		fbuf(const fbuf & other) = delete;
		fbuf& operator=(const fbuf& other) = delete;

		explicit fbuf(PHYSFS_File * file, std::size_t bufferSize = 2048) : file(file), bufferSize(bufferSize)
		{
			buffer = new char[bufferSize];
			char * end = buffer + bufferSize;
			setg(end, end, end);
			setp(buffer, end);
		}

		~fbuf() override
		{
			sync();
			delete [] buffer;
		}
	};

	//-------------------------------------------------------------------------------------

	base_fstream::base_fstream(PHYSFS_File* file) : file(file)
	{
		if (file == nullptr) {
			throw std::invalid_argument("attempted to construct fstream with NULL ptr");
		}
	}

	base_fstream::~base_fstream()
	{
		PHYSFS_close(file);
	}

	PhysFS::size_t base_fstream::length()
	{
		return PHYSFS_fileLength(file);
	}

	//-------------------------------------------------------------------------------------

	PHYSFS_File* openWithMode(char const * filename, mode openMode)
	{
		PHYSFS_File* file = nullptr;
		switch (openMode) {
			case WRITE:
				file = PHYSFS_openWrite(filename);
				break;
			case APPEND:
				file = PHYSFS_openAppend(filename);
				break;
			case READ:
				file = PHYSFS_openRead(filename);
				break;
		}

		if (file == nullptr) {
			throw std::invalid_argument("file not found: " + std::string(filename));
		}

		return file;
	}

	//-------------------------------------------------------------------------------------

	ifstream::ifstream(const string& filename)
		: base_fstream(openWithMode(filename.c_str(), READ)), std::istream(new fbuf(file)) {}

	ifstream::~ifstream() {
		delete rdbuf();
	}

	//-------------------------------------------------------------------------------------

	ofstream::ofstream(const string& filename, mode writeMode)
		: base_fstream(openWithMode(filename.c_str(), writeMode)), std::ostream(new fbuf(file)) {}

	ofstream::~ofstream() {
		delete rdbuf();
	}

	//-------------------------------------------------------------------------------------

	fstream::fstream(const string& filename, mode openMode)
		: base_fstream(openWithMode(filename.c_str(), openMode)), std::iostream(new fbuf(file)) {}

	fstream::~fstream() {
		delete rdbuf();
	}

	//-------------------------------------------------------------------------------------

	Version getLinkedVersion() {
		Version version;
		PHYSFS_getLinkedVersion(&version);
		return version;
	}

	PHYSFS_ErrorCode init(const char* argv0) {
		if(!PHYSFS_init(argv0))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	PHYSFS_ErrorCode deinit() {
		if(!PHYSFS_deinit())
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	ArchiveInfoList supportedArchiveTypes() {
		ArchiveInfoList list;
		for (const ArchiveInfo** archiveType = PHYSFS_supportedArchiveTypes(); *archiveType != nullptr; archiveType++) {
			list.push_back(**archiveType);
		}
		return list;
	}

	string getDirSeparator() {
		return PHYSFS_getDirSeparator();
	}

	void permitSymbolicLinks(bool allow) {
		PHYSFS_permitSymbolicLinks(allow);
	}

	StringList getCdRomDirs() {
		StringList dirs;
		char ** dirBegin = PHYSFS_getCdRomDirs();
		for (char ** dir = dirBegin; *dir != nullptr; dir++) {
			dirs.push_back(*dir);
		}
		PHYSFS_freeList(dirBegin);
		return dirs;
	}

	void getCdRomDirs(StringCallback callback, void * extra) {
		PHYSFS_getCdRomDirsCallback(callback, extra);
	}

	string getBaseDir() {
		return PHYSFS_getBaseDir();
	}

	string getUserDir(const string& org, const string& app) {
		return PHYSFS_getPrefDir(org.c_str(), app.c_str());
	}

	string getWriteDir() {
		return PHYSFS_getWriteDir();
	}

	PHYSFS_ErrorCode setWriteDir(const string& newDir) {
		if(!PHYSFS_setWriteDir(newDir.c_str()))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	PHYSFS_ErrorCode removeFromSearchPath(const string& oldDir) {
		if(!PHYSFS_unmount(oldDir.c_str()))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	StringList getSearchPath() {
		StringList pathList;
		char ** pathBegin = PHYSFS_getSearchPath();
		for (char ** path = pathBegin; *path != nullptr; path++) {
			pathList.push_back(*path);
		}
		PHYSFS_freeList(pathBegin);
		return pathList;
	}

	void getSearchPath(StringCallback callback, void * extra) {
		PHYSFS_getSearchPathCallback(callback, extra);
	}

	void setSaneConfig(const string& orgName, const string& appName,
			const string& archiveExt, bool includeCdRoms, bool archivesFirst) {
		PHYSFS_setSaneConfig(orgName.c_str(), appName.c_str(), archiveExt.c_str(), includeCdRoms, archivesFirst);
	}

	PHYSFS_ErrorCode mkdir(const string& dirName) {
		if(!PHYSFS_mkdir(dirName.c_str()))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	PHYSFS_ErrorCode deleteFile(const string& filename) {
		if(!PHYSFS_delete(filename.c_str()))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	string getRealDir(const string& filename) {
		return PHYSFS_getRealDir(filename.c_str());
	}

	StringList enumerateFiles(const string& directory) {
		StringList files;
		char ** listBegin = PHYSFS_enumerateFiles(directory.c_str());
		for (char ** file = listBegin; *file != nullptr; file++) {
			files.push_back(*file);
		}
		PHYSFS_freeList(listBegin);
		return files;
	}

	bool exists(const string& filename) {
		return PHYSFS_exists(filename.c_str()) != 0;
	}

	bool isDirectory(const string& filename) {
		PHYSFS_Stat stat;
		if(!PHYSFS_stat(filename.c_str(), &stat))
			throw std::runtime_error(string("isDirectory error: ") + std::to_string(PHYSFS_getLastErrorCode()));

		return stat.filetype == PHYSFS_FILETYPE_DIRECTORY;
	}

	bool isSymbolicLink(const string& filename) {
		PHYSFS_Stat stat;
		if(!PHYSFS_stat(filename.c_str(), &stat))
			throw std::runtime_error(string("isSymbolicLink error: ") + std::to_string(PHYSFS_getLastErrorCode()));

		return stat.filetype == PHYSFS_FILETYPE_SYMLINK;
	}

	sint64 getLastModTime(const string& filename) {
		PHYSFS_Stat stat;
		if(!PHYSFS_stat(filename.c_str(), &stat))
			throw std::runtime_error(string("getLastModTime error: ") + std::to_string(PHYSFS_getLastErrorCode()));

		return stat.modtime;
	}

	bool isInit() {
		return PHYSFS_isInit() != 0;
	}

	bool symbolicLinksPermitted() {
		return PHYSFS_symbolicLinksPermitted() != 0;
	}

	void setAllocator(const Allocator* allocator) {
		PHYSFS_setAllocator(allocator);
	}

	PHYSFS_ErrorCode mount(const string& newDir, const string& mountPoint, bool appendToPath) {
		if(!PHYSFS_mount(newDir.c_str(), mountPoint.c_str(), appendToPath))
			return PHYSFS_getLastErrorCode();

		return PHYSFS_ERR_OK;
	}

	string getMountPoint(const string& dir) {
		const auto point = PHYSFS_getMountPoint(dir.c_str());
		if(point == nullptr)
			throw std::runtime_error(string("Failed to get mount point ") + dir);

		return point;
	}

	sint16 Util::swapSLE16(sint16 value) {
		return PHYSFS_swapSLE16(value);
	}

	uint16 Util::swapULE16(uint16 value) {
		return PHYSFS_swapULE16(value);
	}

	sint32 Util::swapSLE32(sint32 value) {
		return PHYSFS_swapSLE32(value);
	}

	uint32 Util::swapULE32(uint32 value) {
		return PHYSFS_swapULE32(value);
	}

	sint64 Util::swapSLE64(sint64 value) {
		return PHYSFS_swapSLE64(value);
	}

	uint64 Util::swapULE64(uint64 value) {
		return PHYSFS_swapULE64(value);
	}

	sint16 Util::swapSBE16(sint16 value) {
		return PHYSFS_swapSBE16(value);
	}

	uint16 Util::swapUBE16(uint16 value) {
		return PHYSFS_swapUBE16(value);
	}

	sint32 Util::swapSBE32(sint32 value) {
		return PHYSFS_swapSBE32(value);
	}

	uint32 Util::swapUBE32(uint32 value) {
		return PHYSFS_swapUBE32(value);
	}

	sint64 Util::swapSBE64(sint64 value) {
		return PHYSFS_swapSBE64(value);
	}

	uint64 Util::swapUBE64(uint64 value) {
		return PHYSFS_swapUBE64(value);
	}

	string Util::utf8FromUcs4(const uint32* src) {
		string value;
		std::size_t length = strlen((char*) src);
		char * buffer = new char[length]; // will be smaller than len
		PHYSFS_utf8FromUcs4(src, buffer, length);
		value.append(buffer);
		return value;
	}

	string Util::utf8ToUcs4(const char* src) {
		string value;
		std::size_t length = strlen(src) * 4;
		char * buffer = new char[length]; // will be smaller than len
		PHYSFS_utf8ToUcs4(src, (uint32*) buffer, length);
		value.append(buffer);
		return value;
	}

	string Util::utf8FromUcs2(const uint16* src) {
		string value;
		std::size_t length = strlen((char*) src);
		char * buffer = new char[length]; // will be smaller than len
		PHYSFS_utf8FromUcs2(src, buffer, length);
		value.append(buffer);
		return value;
	}

	string Util::utf8ToUcs2(const char* src) {
		string value;
		std::size_t length = strlen(src) * 2;
		char * buffer = new char[length]; // will be smaller than len
		PHYSFS_utf8ToUcs2(src, (uint16*) buffer, length);
		value.append(buffer);
		return value;
	}

	string Util::utf8FromLatin1(const char* src) {
		string value;
		std::size_t length = strlen((char*) src) * 2;
		char * buffer = new char[length]; // will be smaller than len
		PHYSFS_utf8FromLatin1(src, buffer, length);
		value.append(buffer);
		return value;
	}
}
