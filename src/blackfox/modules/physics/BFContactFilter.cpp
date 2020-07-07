#include "BFContactFilter.h"

namespace BlackFox
{
    BFContactFilter::BFContactFilter()
    : categoryBits(0x0001)
    , maskBits(0xFFFF)
    , groupIndex(0)
    {}

    BFContactFilter::BFContactFilter(const b2Filter& filter)
    : categoryBits(filter.categoryBits)
    , maskBits(filter.maskBits)
    , groupIndex(filter.groupIndex)
    {}

    BFContactFilter::BFContactFilter(b2Filter&& filter) noexcept
    : categoryBits(filter.categoryBits)
    , maskBits(filter.maskBits)
    , groupIndex(filter.groupIndex)
    {}

    BFContactFilter& BFContactFilter::operator=(const b2Filter& filter)
    {
        categoryBits = filter.categoryBits;
        maskBits = filter.maskBits;
        groupIndex = filter.groupIndex;
        return *this;
    }

    BFContactFilter& BFContactFilter::operator=(b2Filter&& filter) noexcept
    {
        categoryBits = filter.categoryBits;
        maskBits = filter.maskBits;
        groupIndex = filter.groupIndex;
        return *this;
    }

    BFContactFilter::operator b2Filter() const
    {
        b2Filter filter;
        filter.categoryBits = categoryBits;
        filter.maskBits = maskBits;
        filter.groupIndex = groupIndex;
        return filter;
    }
}