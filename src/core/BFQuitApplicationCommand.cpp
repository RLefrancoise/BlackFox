#include "BFQuitApplicationCommand.h"
#include "BFApplication.h"

namespace BlackFox
{
	void BFQuitApplicationCommand::execute(void)
	{
		BFSingleton<BFApplication>::get().quit();
	}

	BFQuitApplicationCommand* BFQuitApplicationCommand::clone(void) const
	{
		return new BFQuitApplicationCommand();
	}
}