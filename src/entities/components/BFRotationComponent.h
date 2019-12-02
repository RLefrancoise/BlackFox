#ifndef BLACKFOX_ROTATION_COMPONENT_H
#define BLACKFOX_ROTATION_COMPONENT_H

#include "BFDegree.h"
#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFRotationComponent : BFComponent<BFRotationComponent>
	{
	    BF_COMPONENT("Rotation")

	    constexpr explicit BFRotationComponent(float degrees)
	    : angle(degrees)
        {}

	    constexpr explicit BFRotationComponent(const BFDegree& a)
	    : angle(a)
        {}

        explicit BFRotationComponent(const BFRadian& a)
        : angle(a)
		{}

		BFDegree angle;
	};
}

#endif