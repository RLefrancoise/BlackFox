#ifndef BLACKFOX_UTILS_H
#define BLACKFOX_UTILS_H

namespace BlackFox
{
	static constexpr bool hasFlag(unsigned int mask, unsigned int flag)
	{
		return (mask & flag) == flag;
	}
}

#endif