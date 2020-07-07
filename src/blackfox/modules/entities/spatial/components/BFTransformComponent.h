#pragma once

#include "BFVector2.h"
#include "BFDegree.h"
#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BLACKFOX_EXPORT BFTransformComponent final : IBFComponent
	{
		BF_COMPONENT(BFTransformComponent, "Transform")

		constexpr BFTransformComponent()
		: BFTransformComponent(BFVector2f(), BFDegree(0), BFVector2f(1,1))
		{}

		constexpr BFTransformComponent(const BFVector2f& position, const BFDegree& rotation, const BFVector2f& scale)
			: position(position)
			, rotation(rotation)
			, scale(scale) {}

		constexpr BFTransformComponent(BFTransformComponent&&) noexcept = default;
		BFTransformComponent& operator=(BFTransformComponent&&) noexcept = default;

		BFVector2f position;
		BFDegree rotation;
		BFVector2f scale;		
	};
}