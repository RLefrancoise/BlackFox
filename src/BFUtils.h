#ifndef BLACKFOX_UTILS_H
#define BLACKFOX_UTILS_H

#include <SDL_hints.h>

namespace BlackFox
{
	static constexpr bool hasFlag(Uint32 mask, Uint32 flag)
	{
		return (mask & flag) == flag;
	}
}

#endif