#include "BFMath.h"

namespace BlackFox::BFMath
{
	inline float clamp(float x, float low, float high)
	{
		if (x < low) x = low;
		else if (x > high) x = high;

		return x;
	}

	inline float wrap(float x, float low, float high)
	{
		if (x < low)
			x = high;
		else if (x > high)
			x = low;

		return x;
	}

	inline float min(float first, float second)
	{
		return (first < second) ? first : second;
	}

	inline float max(float first, float second)
	{
		return (first > second) ? first : second;
	}
}