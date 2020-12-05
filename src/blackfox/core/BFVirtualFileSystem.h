#pragma once

#include <memory>
#include <filesystem>
#include <cinject/cinject.h>

#include "BFApplicationArgs.h"
#include "BFExport.h"

namespace BlackFox
{
    /*!
     * Interface for BlackFox virtual file system
     */
    class BLACKFOX_EXPORT IBFVirtualFileSystem
    {
    public:
        typedef std::shared_ptr<IBFVirtualFileSystem> Ptr;

        virtual ~IBFVirtualFileSystem() = default;

        /*!
         * Init the virtual file system
         *
         * @param args  Application arguments
         *
         * @return      True if initialization is complete, false otherwise
         */
        virtual bool init(BFApplicationArgs::Ptr args) = 0;

        /*!
         * Is the virtual file system initialized ?
         *
         * @return      True if initialized, false otherwise
         */
        virtual bool isInited() = 0;

        /*!
         * Add a path to the list of paths the virtual file system is using to find a file
         *
         * @param folder    Folder to add to the path
         *
         * @return          True if add is successful, false otherwise
         */
        virtual bool addSearchFolder(const std::string& folder) = 0;

        /*!
         * Combine path pieces to form a full path, with the right dir separator according to OS
         *
         * @param path  Path pieces to combine
         *
         * @return      The combined path
         */
        virtual std::string combinePath(const std::vector<std::string>& path) = 0;

        /*!
         * Scan the content of a directory and returns files inside it.
         *
         * @param dirPath   Path of the directory
         * @return          List of files
         */
        virtual std::vector<std::filesystem::path> scanDir(const std::filesystem::path& dirPath) = 0;

        /*!
         * Check if a path is a directory.
         *
         * @param path      Path to check
         * @return          True if path is directory
         */
        virtual bool isDirectory(const std::filesystem::path& path) = 0;

        /*!
         * Check if a path is a file.
         *
         * @param path      Path to check
         * @return          True if path is file
         */
        virtual bool isFile(const std::filesystem::path& path) = 0;

        /*!
         * Check if a path is a symbolic link.
         *
         * @param path      Path to check
         * @return          True if path is symbolic link
         */
        virtual bool isSymbolicLink(const std::filesystem::path& path) = 0;
    };

    /*!
     * Blackfox virtual file system
     */
    class BLACKFOX_EXPORT BFVirtualFileSystem final: public IBFVirtualFileSystem
    {
    public:
        CINJECT(BFVirtualFileSystem());
        ~BFVirtualFileSystem() override;

        bool init(BFApplicationArgs::Ptr args) override;
        bool isInited() override;
        bool addSearchFolder(const std::string& folder) override;

        std::string combinePath(const std::vector<std::string>& path) override;
        std::vector<std::filesystem::path> scanDir(const std::filesystem::path& dirPath) override;
        bool isDirectory(const std::filesystem::path& path) override;
        bool isFile(const std::filesystem::path& path) override;
        bool isSymbolicLink(const std::filesystem::path& path) override;
    };
}