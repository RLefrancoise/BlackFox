#ifndef BLACKFOX_ROTATION_COMPONENT_H
#define BLACKFOX_ROTATION_COMPONENT_H

#include "BFDegree.h"
#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFRotationComponent : BFComponent<BFRotationComponent>
	{
	    BF_COMPONENT("Rotation")

	    explicit BFRotationComponent(float degrees)
        {
	        angle = degrees;
        }

	    explicit BFRotationComponent(BFDegree a)
        {
	        angle = a;
        }

		BFDegree angle;
	};
}

#endif