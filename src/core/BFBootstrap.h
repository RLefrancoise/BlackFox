#ifndef BLACKFOX_BOOTSTRAP_H
#define BLACKFOX_BOOTSTRAP_H

#include "BFNonCopyable.h"

namespace BlackFox
{
	class BFBootstrap : private BFNonCopyable
	{
	public:
		int run() const;
	};
}

#endif