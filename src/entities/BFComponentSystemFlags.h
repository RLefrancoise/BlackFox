#ifndef BLACKFOX_COMPONENTSYSTEMFLAGS_H
#define BLACKFOX_COMPONENTSYSTEMFLAGS_H

namespace BlackFox
{
	enum ComponentSystemGroups
	{
		GameLoop		= 1 << 0,
		Render			= 1 << 1,
		EndOfFrame		= 1 << 2
	};
}

#endif