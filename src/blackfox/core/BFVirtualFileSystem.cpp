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

        //Mount base dir
        if(const auto err = PhysFS::mount(m_baseDir.string(), true) != PHYSFS_ERR_OK)
        {
            BF_ERROR("Failed to mount base folder: {}", err);
            return false;
        }

        BF_PRINT("Mount base folder to virtual file system at location {}", m_baseDir.string());

        //Add data to search folder
        addSearchFolder("data");

        return true;
    }

    bool BFVirtualFileSystem::addSearchFolder(const std::string &folder)
    {
        const auto res = PhysFS::mount(combinePath({m_baseDir.string(), folder}), false);
        BF_PRINT("Search path is: {}", Utils::join(PhysFS::getSearchPath(), ","));
        return res;
    }

    bool BFVirtualFileSystem::isInited()
    {
        return PhysFS::isInit();
    }

    std::string BFVirtualFileSystem::combinePath(const std::vector<std::string> &path)
    {
        return Utils::join(path, getDirSeparator());
    }

    std::string BFVirtualFileSystem::getDirSeparator()
    {
        return PhysFS::getDirSeparator();
    }

    std::vector<std::filesystem::path> BFVirtualFileSystem::getSearchFolders()
    {
        const auto folders = PhysFS::getSearchPath();
        std::vector<std::filesystem::path> paths;
        paths.reserve(folders.size());

        for(const auto& folder : folders)
        {
            paths.emplace_back(std::filesystem::path(folder));
        }

        return paths;
    }

    std::filesystem::path BFVirtualFileSystem::getBaseDir()
    {
        return m_baseDir;
    }

    std::vector<std::filesystem::path> BFVirtualFileSystem::scanDir(const std::filesystem::path& dirPath)
    {
        const auto list = PhysFS::enumerateFiles(dirPath.string());

        std::vector<std::filesystem::path> files;
        files.reserve(list.size());

        for (const auto &file : list)
        {
            files.emplace_back(file);
        }

        return files;
    }

    std::vector<std::filesystem::path> BFVirtualFileSystem::scanDirRecursive(const std::filesystem::path& dirPath)
    {
        const auto list = PhysFS::enumerateFiles(dirPath.string());

        std::vector<std::filesystem::path> files;

        for (const auto &file : list)
        {
            if(isSymbolicLink(file)) continue;

            files.emplace_back(file);

            if(isDirectory(file))
            {
                const auto subDirFiles = scanDirRecursive(file);
                for(const auto& subFile : subDirFiles)
                {
                    files.emplace_back(file / subFile);
                }
            }
        }

        return files;
    }

    void BFVirtualFileSystem::getContent(const std::filesystem::path& path, std::string* content)
    {
        auto ifs = PhysFS::ifstream(path.string());
        if(!ifs.good())
        {
            BF_EXCEPTION("Failed to get content from path {}", path.string());
        }

        const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        *content = str;

        //ifs >> *content;
    }

    std::size_t BFVirtualFileSystem::getBytes(const std::filesystem::path& path, char** buffer)
    {        
        auto ifs = PhysFS::ifstream(path.string());
        if(!ifs.good())
        {
            BF_EXCEPTION("Failed to get bytes from path {}", path.string());
        }

        *buffer = new char[ifs.length()];
        ifs.read(*buffer, ifs.length());

        return ifs.length();
    }

    bool BFVirtualFileSystem::isDirectory(const std::filesystem::path& path)
    {
        return PhysFS::exists(path.string()) && PhysFS::isDirectory(path.string());
    }

    bool BFVirtualFileSystem::isFile(const std::filesystem::path& path)
    {
        return !isDirectory(path) && !isSymbolicLink(path);
    }

    bool BFVirtualFileSystem::isSymbolicLink(const std::filesystem::path &path)
    {
        return PhysFS::symbolicLinksPermitted() && PhysFS::exists(path.string()) && PhysFS::isSymbolicLink(path.string());
    }
}