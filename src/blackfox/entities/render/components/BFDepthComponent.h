#pragma once

#include "BFComponent.h"

namespace BlackFox::Components
{
	/*!
	 * Depth component
	 */
	struct BLACKFOX_EXPORT BFDepthComponent final : IBFComponent
	{
		BF_COMPONENT("Depth")

		/*!
		 * Depth value
		 */
		int depth;
	};
}