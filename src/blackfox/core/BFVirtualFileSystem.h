#pragma once

#include <memory>
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
         * @param argv  First argument received by the program (usually the full path to the program executable)
         * @param args  Application arguments
         *
         * @return      True if initialization is complete, false otherwise
         */
        virtual bool init(const char* argv, BFApplicationArgs::Ptr args) = 0;

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
    };

    /*!
     * Blackfox virtual file system
     */
    class BLACKFOX_EXPORT BFVirtualFileSystem final: public IBFVirtualFileSystem
    {
    public:
        CINJECT(BFVirtualFileSystem());
        ~BFVirtualFileSystem() override;

        bool init(const char* argv, BFApplicationArgs::Ptr args) override;
        bool isInited() override;
        bool addSearchFolder(const std::string& folder) override;

        std::string combinePath(const std::vector<std::string>& path) override;
    };
}