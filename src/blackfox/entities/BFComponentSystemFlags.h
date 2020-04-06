#ifndef BLACKFOX_COMPONENTSYSTEMFLAGS_H
#define BLACKFOX_COMPONENTSYSTEMFLAGS_H

namespace BlackFox
{
	enum class ComponentSystemGroups
	{
		GameLoop		= 1 << 0,
		Render			= 1 << 1,
		EndOfFrame		= 1 << 2,
		FixedTime		= 1 << 3
	};
}

#endif