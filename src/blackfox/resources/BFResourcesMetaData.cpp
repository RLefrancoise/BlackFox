#include "BFResourcesMetaData.h"

namespace BlackFox
{
    BFResourcesMetaData::BFResourcesMetaData(const ResourceGuid& guid, const BFString& path, const Resources::ResourceType& type)
    {
        this->guid = guid;
        this->path = path;
        this->type = type;
    }
}