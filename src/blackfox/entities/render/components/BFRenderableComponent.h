#pragma once

#include "BFComponent.h"

namespace BlackFox::Components
{
	/*!
	 * Renderable component
	 */
	struct BLACKFOX_EXPORT BFRenderableComponent final : IBFComponent
	{
		BF_COMPONENT("Renderable")
	};
}
