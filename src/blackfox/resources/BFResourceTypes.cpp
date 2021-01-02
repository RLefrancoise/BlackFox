#include "BFResourceTypes.h"
#include <algorithm>

namespace BlackFox::Resources
{
    bool ResourceCategoryCompare::operator()(const ResourceCategory& lhs, const ResourceCategory& rhs) const
    {
        return lhs.value() < rhs.value();
    }

    std::size_t ResourceCategoryCompare::operator()(const ResourceCategory& c) const
    {
        return std::hash<std::string>{}(std::to_string(c.value()));
    }

    ResourceCategory getResourceTypeCategory(const ResourceType& type)
    {
        for(const auto& entry : TYPES_CATEGORIES)
        {
            if (std::find(entry.second.begin(), entry.second.end(), type) != entry.second.end())
                return entry.first;
        }

        return UNKNOWN_CATEGORY;
    }

    Resources::ResourceType getTypeFromResource(const BFString& path)
    {
        const std::filesystem::path p(path);
        const auto extension = p.extension().string();
        if(extension == ".lua")
        {
            if(path.find("components") == 0) return Resources::LUA_COMPONENT_SCRIPT;
            if(path.find("systems") == 0) return Resources::LUA_SYSTEM_SCRIPT;
        }
        else if(extension == ".png")
        {
            return Resources::TEXTURE_ASSET;
        }
        else if(extension == ".ttf")
        {
            return Resources::FONT_ASSET;
        }

        return Resources::UNKNOWN_TYPE;
    }

    /*ResourceGuid pathToGuid(const std::string& path)
    {
        return ResourceGuid(path.c_str());
    }

    std::filesystem::path guidToPath(const ResourceGuid& guid)
    {
        return std::filesystem::path{guid.data()};
    }*/
}