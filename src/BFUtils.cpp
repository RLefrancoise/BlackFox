#include "BFUtils.h"

namespace BlackFox
{
	bool hasFlag(Uint32 mask, Uint32 flag)
	{
		return (mask & flag) == flag;
	}
}