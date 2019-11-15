#ifndef BLACKFOX_QUITAPPLICATIONCOMMAND_H
#define BLACKFOX_QUITAPPLICATIONCOMMAND_H

#include "BFCommand.h"

namespace BlackFox
{
	class BFQuitApplicationCommand : public BFCommand
	{
	public:
		BFQuitApplicationCommand() {}
		BFQuitApplicationCommand(const BFQuitApplicationCommand& cmd) {}

		virtual void execute(void);
		virtual BFQuitApplicationCommand* clone(void) const;
	};
}

#endif