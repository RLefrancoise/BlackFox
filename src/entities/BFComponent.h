#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

#include <string>

namespace BlackFox
{
    template <typename C>
	struct BFComponent
	{
	    BFComponent() = default;
	    BFComponent(const BFComponent&) = default;
	    BFComponent(BFComponent&&) noexcept = default;
	    virtual ~BFComponent() noexcept = default;

	    BFComponent<C>& operator=(const BFComponent<C>&) = default;
	};
}

#define BF_COMPONENT(componentName) const char* name = "componentName";

#endif