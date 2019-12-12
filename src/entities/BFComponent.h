#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

namespace BlackFox
{
	struct IBFComponent
	{
	public:
		virtual ~IBFComponent() noexcept = default;
	};
}

#define BF_COMPONENT(componentName)          static constexpr const char *name = componentName;

#endif