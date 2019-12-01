#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

namespace BlackFox
{
    template <typename C>
	struct BFComponent
	{
	    constexpr BFComponent() = default;
	    constexpr BFComponent(const BFComponent&) = default;
	    constexpr BFComponent(BFComponent&&) noexcept = default;
	    virtual ~BFComponent() noexcept = default;

	    constexpr BFComponent<C>& operator=(const BFComponent<C>&) = default;
	};
}

#define BF_COMPONENT(componentName)	static constexpr const char* name = "componentName";

#endif