#pragma once

#include <entt/resource/loader.hpp>
#include <filesystem>
#include <physfs.hpp>
#include <SFML/System/MemoryInputStream.hpp>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFResourceTypes.h"
#include "BFVirtualFileInputStream.h"
#include "BFVirtualFileSystem.h"
#include "BFResourcesHolder.h"

namespace BlackFox
{
    /*!
     * Template for resource loader
     *
     * @tparam Loader       Loader class
     * @tparam Resource     Resource class
     */
    template<class Loader, class Resource>
    struct BFResourceLoader : entt::resource_loader<Loader, Resource>
    {
        /*!
         * Get the sub folders where this kind of resources should be placed
         * 
         * @return  The name of the sub folder 
         */
        virtual std::string subFolder() const = 0;

        template<typename... Args>
        [[nodiscard]] std::shared_ptr<Resource> load(
                const Resources::ResourceType& type,
                const BFResourcesMetaData& data,
                const IBFVirtualFileSystem::Ptr& vfs,
                Args... args) const
        {
            auto res = createResource(type, data.guid);
            return load(data, res, vfs, std::forward<Args>(args)...);
        }

        template<typename... Args>
        [[nodiscard]] std::shared_ptr<Resource> createResource(Args... args) const
        {
            return std::make_shared<Resource>(std::forward<Args>(args)...);
        }

        template<typename... Args>
        std::shared_ptr<Resource> load(
                const BFResourcesMetaData& data,
                std::shared_ptr<Resource> res,
                const IBFVirtualFileSystem::Ptr& vfs,
                Args... args) const
        {
            //Prepend sub folder if there is any
            //if(subFolder() != "") vfs->addSearchFolder(subFolder());

            // Create stream
            auto stream = std::make_unique<BFVirtualFileInputStream>(data.path, vfs);
            if(!stream->isOpened())
            {
                BF_EXCEPTION("Failed to open virtual file input stream for resource {}", data.path.string());
            }

            // Load resource
            const auto loadSuccess = static_cast<const Loader*>(this)->loadResource(
                    res.get(),
                    std::move(stream),
                    std::forward<Args>(args)...);

            //If failed to load, throw
            if(!loadSuccess)
            {
                BF_EXCEPTION("Failed to load resource {}", data.path.string());
            }

            return res;
        }

        /*!
         * Load a resource from a Guid
         *
         * @tparam Args     Arguments types to use to load the resource
         * @param guid      Resource Guid
         * @param vfs       Virtual file system
         * @param args      Arguments to use to load the resource
         *
         * @return          A pointer to the resource
         */
        template<typename... Args>
        [[nodiscard]] std::shared_ptr<Resource> load(
                const BFResourcesMetaData& data,
                const IBFVirtualFileSystem::Ptr& vfs,
                Args... args) const
        {
            auto resource = createResource();
            return load(data, resource, vfs);
        }
    };
}