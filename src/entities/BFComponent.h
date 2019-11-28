#ifndef BLACKFOX_COMPONENT_H
#define BLACKFOX_COMPONENT_H

#include <string>

namespace BlackFox
{
	struct BFComponent
	{
		std::string name() const
		{
			return typeid(this).name();
		}
	};
}

#endif