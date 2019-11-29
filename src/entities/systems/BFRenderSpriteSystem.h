#ifndef BLACKFOX_RENDER_SPRITE_SYSTEM_H
#define BLACKFOX_RENDER_SPRITE_SYSTEM_H

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	class BFRenderSpriteSystem : public BFComponentSystem
	{
        BF_SYSTEM_AUTO_CREATE(BFRenderSpriteSystem, Render)

	public:
		CINJECT(BFRenderSpriteSystem(std::shared_ptr<BFApplication> application));
		void update(float dt) override;
	};
}

#endif