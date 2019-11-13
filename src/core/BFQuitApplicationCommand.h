#ifndef BLACKFOX_QUITAPPLICATION_COMMAND
#define BLACKFOX_QUITAPPLICATION_COMMAND

#include "BFCommand.h"

namespace BlackFox
{
	class BFQuitApplicationCommand : public BFCommand
	{
	public:
		virtual void execute(void);
		virtual BFQuitApplicationCommand* clone(void) const;
	};
}

#endif