#include "BFVirtualFileSystem.h"
#include "BFDebug.h"
#include "BFStringUtils.h"

#include <physfs.hpp>

namespace BlackFox
{
    std::string dataFolder;

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

        //Mount data folder
        dataFolder = combinePath({static_cast<std::string>(args->baseFolder()), "data"});

        if(const auto err = PhysFS::mount(dataFolder, true) != PHYSFS_ERR_OK)
        {
            BF_ERROR("Failed to mount data folder: {}", err);
            return false;
        }

        BF_PRINT("Mount data folder to virtual file system at location {}", dataFolder);

        return true;
    }

    bool BFVirtualFileSystem::addSearchFolder(const std::string &folder)
    {
        const auto res = PhysFS::mount(combinePath({dataFolder, folder}), false);
        BF_PRINT("Search path is: {}", Utils::join(PhysFS::getSearchPath(), ","));
        return res;
    }

    bool BFVirtualFileSystem::isInited()
    {
        return PhysFS::isInit();
    }

    std::string BFVirtualFileSystem::combinePath(const std::vector<std::string> &path)
    {
        return Utils::join(path, PhysFS::getDirSeparator());
    }

    std::vector<std::filesystem::path> BFVirtualFileSystem::scanDir(const std::filesystem::path& dirPath)
    {
        std::vector<std::filesystem::path> files;
        const auto list = PhysFS::enumerateFiles(dirPath.string());

        for (const auto &file : list)
        {
            files.emplace_back(file);
        }

        return files;
    }

    bool BFVirtualFileSystem::isDirectory(const std::filesystem::path& path)
    {
        return PhysFS::isDirectory(path.string());
    }

    bool BFVirtualFileSystem::isFile(const std::filesystem::path& path)
    {
        return !isDirectory(path) && !isSymbolicLink(path);
    }

    bool BFVirtualFileSystem::isSymbolicLink(const std::filesystem::path &path)
    {
        return PhysFS::isSymbolicLink(path.string());
    }
}