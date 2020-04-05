#ifndef BLACKFOX_RENDER_SPRITE_SYSTEM_H
#define BLACKFOX_RENDER_SPRITE_SYSTEM_H

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// Render Sprite system.
	/// </summary>
	/// --------------------------------------------------------------------------------
	class BFRenderSpriteSystem final : public BFComponentSystem
	{
        BF_SYSTEM_AUTO_CREATE(BFRenderSpriteSystem, ComponentSystemGroups::Render, "RenderSpriteSystem")

	public:
		CINJECT(BFRenderSpriteSystem(std::shared_ptr<BFApplication> application));
		void update(float dt) override;
	};
}

#endif