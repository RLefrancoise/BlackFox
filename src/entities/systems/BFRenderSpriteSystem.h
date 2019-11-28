#ifndef BLACKFOX_RENDER_SPRITE_SYSTEM_H
#define BLACKFOX_RENDER_SPRITE_SYSTEM_H

#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	class BFRenderSpriteSystem : public BFComponentSystem
	{
	public:
		CINJECT(BFRenderSpriteSystem(std::shared_ptr<BFApplication> application));
		void update(float dt) override;
	};
}

#endif