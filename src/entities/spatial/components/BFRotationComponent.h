#ifndef BLACKFOX_ROTATION_COMPONENT_H
#define BLACKFOX_ROTATION_COMPONENT_H

#include "BFComponent.h"
#include "BFDegree.h"
#include "BFRadian.h"

namespace BlackFox::Components
{
	struct BFRotationComponent : public IBFComponent
	{
	    BF_COMPONENT("Rotation")

		constexpr BFRotationComponent() 
		: angle(0) 
		{}

	    constexpr explicit BFRotationComponent(const float degrees)
	    : angle(degrees)
        {}

	    constexpr explicit BFRotationComponent(const BFDegree& a)
	    : angle(a)
        {}

		constexpr explicit BFRotationComponent(BFDegree&& a)
		: angle(std::move(a))
		{}

        explicit BFRotationComponent(const BFRadian& a)
        : angle(a)
		{}

		explicit BFRotationComponent(BFRadian&& a)
		: angle(a)
		{}

		BFDegree angle;
	};
}

#endif