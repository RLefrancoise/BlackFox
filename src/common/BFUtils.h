#ifndef BLACKFOX_UTILS_H
#define BLACKFOX_UTILS_H

namespace BlackFox
{
	static constexpr bool hasFlag(const unsigned int mask, const unsigned int flag)
	{
		return (mask & flag) == flag;
	}
}

#endif