#include "BFVirtualFileSystem.h"
#include "BFDebug.h"

#include <physfs.hpp>
#include <fmt/format.h>
#include <filesystem>

namespace BlackFox
{
    BFVirtualFileSystem::BFVirtualFileSystem() = default;

    BFVirtualFileSystem::~BFVirtualFileSystem()
    {
        if(isInited()) {
            BF_PRINT("Deinit virtual file system");
            PhysFS::deinit();
        }
    }

    bool BFVirtualFileSystem::init(const char *argv)
    {
        //Init
        if(const auto err = PhysFS::init(argv) != PHYSFS_ERR_OK) {
            BF_ERROR("Failed to initialize virtual file system: {}", err);
            return false;
        }

        BF_PRINT("Init virtual file system");

        //No symlink
        PhysFS::permitSymbolicLinks(false);

        //Mount data folder
        const auto dataFolder = fmt::format("{}{}data", std::filesystem::current_path().string(), PhysFS::getDirSeparator());
        if(const auto err = PhysFS::mount(dataFolder, true) != PHYSFS_ERR_OK) {
            BF_ERROR("Failed to mount data folder: {}", err);
            return false;
        }

        BF_PRINT("Mount data folder to virtual file system");

        return true;
    }

    bool BFVirtualFileSystem::addSearchFolder(const std::string &folder)
    {
        return PhysFS::mount(folder, "data", true);
    }

    bool BFVirtualFileSystem::isInited()
    {
        return PhysFS::isInit();
    }

    std::string BFVirtualFileSystem::combinePath(const std::vector<std::string> &path)
    {
        std::string result;

        for(auto it = path.cbegin(); it != path.cend();)
        {
            result += *it;
            ++it;
            if(it != path.cend()) result += PhysFS::getDirSeparator();
        }

        return result;
    }
}