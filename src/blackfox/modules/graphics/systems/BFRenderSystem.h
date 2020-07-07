#pragma once

#include <cinject/cinject.h>
#include <SFML/Graphics/View.hpp>

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"
#include "BFRenderLayers.h"

namespace BlackFox::Systems
{
	/*!
	 * Render system. It renders all stuff that can be displayed (basically, all renderable components).
	 */
	class BLACKFOX_EXPORT BFRenderSystem final : public BFComponentSystemBase<BFRenderSystem>
	{
        BF_SYSTEM_AUTO_CREATE(BFRenderSystem, ComponentSystemGroups::Render, "RenderSystem")

	public:
		CINJECT(BFRenderSystem(std::shared_ptr<BFApplication> application, std::shared_ptr<BFWorld> world));
		void update(float dt) override;

	private:
		/*!
		 * Execute a render pass. Basically, it is called for each view component in the world. If no view, it it called
		 * once with the default view.
		 *
		 * @param view		The view to use for the pass
		 * @param layers	Layers to render
		 */
		void renderPass(const sf::View& view, Graphics::BFRenderLayers layers);
	};
}