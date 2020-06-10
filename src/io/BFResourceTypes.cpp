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
}