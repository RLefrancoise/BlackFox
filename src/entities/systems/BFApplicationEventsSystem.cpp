#include "BFApplicationEventsSystem.h"
#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFApplicationEventsSystem, "BFApplicationEventsSystem")

namespace BlackFox::Systems
{
	BFApplicationEventsSystem::BFApplicationEventsSystem(BFApplication::Ptr application)
	: BFComponentSystem(std::move(application))
	{
	}

	void BFApplicationEventsSystem::onEvent(const sdl::Event & ev)
	{
		switch(ev.type)
		{
		case SDL_QUIT:
			m_application->commandManager()->createCommand<BFQuitApplicationCommand>()->execute();
			break;
		}
	}
}
