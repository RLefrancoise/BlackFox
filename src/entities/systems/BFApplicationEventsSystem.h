#ifndef BLACKFOX_APPLICATION_EVENTS_SYSTEM_H
#define BLACKFOX_APPLICATION_EVENTS_SYSTEM_H

#include <cinject/cinject.h>

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	class BFApplicationEventsSystem : public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFApplicationEventsSystem, EndOfFrame)
	public:
		CINJECT(BFApplicationEventsSystem(std::shared_ptr<BFApplication> application));
		void onEvent(const sdl::Event& ev) override;
	};
}

#endif