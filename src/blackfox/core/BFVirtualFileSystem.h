#pragma once

#include <memory>
#include <cinject/cinject.h>
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
        virtual bool init(const char* argv) = 0;
    };


    class BLACKFOX_EXPORT BFVirtualFileSystem final: public IBFVirtualFileSystem
    {
    public:
        CINJECT(BFVirtualFileSystem());
        ~BFVirtualFileSystem() override;

        bool init(const char* argv) override;
    };
}