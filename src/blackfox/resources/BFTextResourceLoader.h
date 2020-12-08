#pragma once

#include "BFTextResource.h"
#include "BFResourceLoader.h"

namespace BlackFox
{
    struct BLACKFOX_EXPORT BFTextResourceLoader final : BFResourceLoader<BFTextResourceLoader, BFTextResource>
    {
        std::string subFolder() const override
        {
            return "";
        }

        /*!
         * Load a text asset from memory
         *
         * @param text      Text asset to load
         * @param stream    stream to use to load the text asset
         *
         * @return          True if load success, false otherwise
         */
        [[nodiscard]] bool loadResource(
                BFTextResource* text,
                std::unique_ptr<BFVirtualFileInputStream>&& stream) const
        {
            std::string err;
            if(!text->load(*stream, &err))
            {
                BF_ERROR("Failed to load text asset: {}", err);
                return false;
            }

            return true;
        }
    };
}