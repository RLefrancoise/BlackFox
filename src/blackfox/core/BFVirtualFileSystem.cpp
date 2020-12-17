#include "BFVirtualFileSystem.h"
#include "BFDebug.h"
#include "BFStringUtils.h"

#include <physfs.hpp>

namespace BlackFox
{
    BFVirtualFileSystem::BFVirtualFileSystem() = default;

    BFVirtualFileSystem::~BFVirtualFileSystem()
    {
        if(isInited())
        {
            BF_PRINT("Deinit virtual file system");
            PhysFS::deinit();
        }
    }

    bool BFVirtualFileSystem::init(BFApplicationArgs::Ptr args)
    {
        //Init
        if(const auto err = PhysFS::init(args->argc() > 0 ? args->argv()[0] : nullptr) != PHYSFS_ERR_OK)
        {
            BF_ERROR("Failed to initialize virtual file system: {}", err);
            return false;
        }

        BF_PRINT("Init virtual file system");

        //No symlink
        PhysFS::permitSymbolicLinks(false);

        m_baseDir = args->baseFolder();

        //Mount data folder
        if(const auto err = PhysFS::mount(m_baseDir, true) != PHYSFS_ERR_OK)
        {
            BF_ERROR("Failed to mount base folder: {}", err);
            return false;
        }

        BF_PRINT("Mount base folder to virtual file system at location {}", m_baseDir);

        //Add data to search folder
        addSearchFolder("data");

        return true;
    }

    bool BFVirtualFileSystem::addSearchFolder(const BFString& folder)
    {
        const auto res = PhysFS::mount(combinePath({m_baseDir, folder}), false);
        BF_PRINT("Search path is: {}", Utils::join(PhysFS::getSearchPath(), ","));
        return res;
    }

    bool BFVirtualFileSystem::isInited()
    {
        return PhysFS::isInit();
    }

    BFString BFVirtualFileSystem::combinePath(const std::vector<BFString>& path)
    {
        return Utils::join(path, getDirSeparator());
    }

    BFString BFVirtualFileSystem::getDirSeparator()
    {
        return PhysFS::getDirSeparator();
    }

    std::vector<BFString> BFVirtualFileSystem::getSearchFolders()
    {
        const auto folders = PhysFS::getSearchPath();
        std::vector<BFString> paths;
        paths.reserve(folders.size());

        for(const auto& folder : folders)
        {
            paths.emplace_back(folder);
        }

        return paths;
    }

    BFString BFVirtualFileSystem::getBaseDir()
    {
        return m_baseDir;
    }

    std::vector<BFString> BFVirtualFileSystem::scanDir(const BFString& dirPath)
    {
        const auto list = PhysFS::enumerateFiles(dirPath);

        std::vector<BFString> files;
        files.reserve(list.size());

        for (const auto &file : list)
        {
            files.emplace_back(file);
        }

        return files;
    }

    std::vector<BFString> BFVirtualFileSystem::scanDirRecursive(const BFString& dirPath)
    {
        const auto list = PhysFS::enumerateFiles(dirPath);

        std::vector<BFString> files;

        for (const auto &file : list)
        {
            if(isSymbolicLink(file)) continue;

            files.emplace_back(file);

            if(isDirectory(file))
            {
                const auto subDirFiles = scanDirRecursive(file);
                for(const auto& subFile : subDirFiles)
                {
                    files.emplace_back(combinePath({file, subFile}));
                }
            }
        }

        return files;
    }

    void BFVirtualFileSystem::getContent(const BFString& path, BFString* content)
    {
        if(!exists(path))
        {
            BF_EXCEPTION("File {} does not exist", path);
        }

        auto ifs = PhysFS::ifstream(path);
        if(!ifs.good())
        {
            BF_EXCEPTION("Failed to get content from path {}", std::string(path));
        }

        const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        *content = str;
    }

    std::size_t BFVirtualFileSystem::getBytes(const BFString& path, char** buffer)
    {
        if(!exists(path))
        {
            BF_EXCEPTION("File {} does not exist", path);
        }

        auto ifs = PhysFS::ifstream(path);
        if(!ifs.good())
        {
            BF_EXCEPTION("Failed to get bytes from path {}", std::string(path));
        }

        *buffer = new char[ifs.length()];
        ifs.read(*buffer, ifs.length());

        return ifs.length();
    }

    bool BFVirtualFileSystem::isDirectory(const BFString& path)
    {
        return PhysFS::exists(path) && PhysFS::isDirectory(path);
    }

    bool BFVirtualFileSystem::isFile(const BFString& path)
    {
        return !isDirectory(path) && !isSymbolicLink(path);
    }

    bool BFVirtualFileSystem::isSymbolicLink(const BFString& path)
    {
        return PhysFS::symbolicLinksPermitted() && PhysFS::exists(path) && PhysFS::isSymbolicLink(path);
    }

    bool BFVirtualFileSystem::exists(const BFString& path)
    {
        return PhysFS::exists(path);
    }
}