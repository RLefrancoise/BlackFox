#ifndef BLACKFOX_MAINCONTEXT_H
#define BLACKFOX_MAINCONTEXT_H

#include "BFBaseContext.h"

namespace BlackFox
{
	class BFMainContext : public BFBaseContext
	{
	public:
		explicit BFMainContext(DiContainer container);
	};
}

#endif