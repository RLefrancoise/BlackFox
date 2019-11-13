#include "BFQuitApplicationCommand.h"
#include "BFApplication.h"

#include <rttr/registration.h>

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

RTTR_REGISTRATION
{
	using namespace rttr;
	using namespace BlackFox;

	registration::class_<BFQuitApplicationCommand>("BFQuitApplicationCommand")
		.constructor<>()
		.method("execute", &BFQuitApplicationCommand::execute)
		.method("clone", &BFQuitApplicationCommand::clone);
}