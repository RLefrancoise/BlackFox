#pragma once

#include "BFVector2.h"
#include "BFDegree.h"
#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFTransformComponent : IBFComponent
	{
		BF_COMPONENT("Transform")

		constexpr BFTransformComponent() = default;
		constexpr BFTransformComponent(const BFVector2f& position, const BFDegree& rotation, const BFVector2f& scale)
			: position(position)
			, rotation(rotation)
			, scale(scale) {}

		BFVector2f position;
		BFDegree rotation;
		BFVector2f scale;		
	};
}