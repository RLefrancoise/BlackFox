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

		constexpr BFDepthComponent() : BFDepthComponent(0) {}
		constexpr explicit BFDepthComponent(int depth) : depth(depth) {}

		constexpr BFDepthComponent(BFDepthComponent&&) noexcept = default;
		BFDepthComponent& operator=(BFDepthComponent&&) noexcept = default;

		/*!
		 * Depth value
		 */
		int depth;
	};
}