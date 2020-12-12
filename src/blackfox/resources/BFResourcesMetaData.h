#pragma once

#include "BFExport.h"
#include "BFTypeDefs.h"
#include "BFResourceTypes.h"

namespace BlackFox
{
    struct BLACKFOX_EXPORT BFResourcesMetaData
    {
        explicit BFResourcesMetaData(const ResourceGuid& guid, const std::filesystem::path& path, const Resources::ResourceType& type);

        ResourceGuid guid;
        std::filesystem::path path;
        Resources::ResourceType type;
    };
}