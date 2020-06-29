#pragma once

#include <cinject/cinject.h>

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// Render Sprite system.
	/// </summary>
	/// --------------------------------------------------------------------------------
	class BLACKFOX_EXPORT BFRenderSystem final : public BFComponentSystem
	{
		//BF_SYSTEM(BFRenderSystem, "RenderSystem", ComponentSystemGroups::Render)
        BF_SYSTEM_AUTO_CREATE(BFRenderSystem, ComponentSystemGroups::Render, "RenderSystem")

	public:
		CINJECT(BFRenderSystem(std::shared_ptr<BFApplication> application, std::shared_ptr<BFWorld> world));
		void update(float dt) override;
	};
}