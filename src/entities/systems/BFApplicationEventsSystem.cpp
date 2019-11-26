#include "BFApplicationEventsSystem.h"
#include "BFApplication.h"
#include "BFQuitApplicationCommand.h"

namespace BlackFox::Systems
{
	BFApplicationEventsSystem::BFApplicationEventsSystem(std::shared_ptr<BFApplication> application) : BFComponentSystem(application)
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

	void BFApplicationEventsSystem::update(float dt)
	{
	}
}
