#pragma once

#include "BFExport.h"
#include "BFTypeDefs.h"
#include "BFResourceTypes.h"

namespace BlackFox
{
    struct BLACKFOX_EXPORT BFResourcesMetaData
    {
        explicit BFResourcesMetaData(const ResourceGuid& guid, const BFString& path, const Resources::ResourceType& type);

        ResourceGuid guid;
        BFString path;
        Resources::ResourceType type;
    };
}