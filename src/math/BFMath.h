#ifndef BLACKFOX_MATH_H
#define BLACKFOX_MATH_H

#include "BFVector2.h"
#include "BFRadian.h"

namespace BlackFox
{
	namespace BFMath
	{
		/*! \brief	The smallest value between two floats. */
		constexpr float EPSILON = 0.00001f;
		/*! \brief	The value of PI. */
		constexpr float PI = 3.1415926535897932384626433832795f;
		/*! \brief	The value of PI/2. */
		constexpr float HALF_PI = PI * 0.5f;
		/*! \brief	The value of 2PI. */
		constexpr float TWO_PI = PI * 2.0f;

		/*!
		 * \fn	T clamp(T x, T low, T high);
		 *
		 * \brief	If x is smaller than low, x equals low. If x is larger than high, x equals high. Otherwise x is unchanged.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	x   	The value to clamp.
		 * \param	low 	The low limit.
		 * \param	high	The high limit.
		 *
		 * \returns	The clamped value.
		 */
		template <typename T>
		float clamp(T x, T low, T high)
		{
			if (x < low) x = low;
			else if (x > high) x = high;

			return x;
		}

		/*!
		 * \fn	T wrap(T x, T low, T high);
		 *
		 * \brief	If x is below the low value it will return the high value, if x is higher than the high value, it will return the low value
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	x   	The value to wrap.
		 * \param	low 	The low limit.
		 * \param	high	The high limit.
		 *
		 * \returns	The wrapped value.
		 */
		template <typename T>
		T wrap(T x, T low, T high)
		{
			if (x < low)
				x = high;
			else if (x > high)
				x = low;

			return x;
		}

		/*!
		 * \fn	T min(T first, T second);
		 *
		 * \brief	Determines the minimum of the given parameters.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	first	The first value.
		 * \param	second	The second value.
		 *
		 * \returns	The minimum value.
		 */
		template <typename T>
		T min(T first, T second)
		{
			return (first < second) ? first : second;
		}

		/*!
		 * \fn	T max(T first, T second);
		 *
		 * \brief	Determines the maximum of the given parameters.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	first 	The first value.
		 * \param	second	The second value.
		 *
		 * \returns	The maximum value.
		 */
		template <typename T>
		T max(T first, T second)
		{
			return (first > second) ? first : second;
		}

		/*!
		 * \fn	template<typename T> T lerp(T start, T end, float time)
		 *
		 * \brief	A linear interpolation of start to end based on the input time.
		 *
		 * \typeparam	T	Type of the value to lerp.
		 * \param	start	The start value.
		 * \param	end  	The end value.
		 * \param	time 	The interpolation time, between 0 and 1.
		 *
		 * \returns	The interpolated value.
		 */
		template<typename T>
		T lerp(T start, T end, float time)
		{
			T diff = end - start;
			return static_cast<T>(start + diff * time);
		}

		/*!
		 * Get direction vector from a given angle
		 *
		 * @param angle 	Angle
		 * @return 			Direction vector
		 */
		BLACKFOX_EXPORT BFVector2f direction(const BFRadian& angle);
	}
}

#endif
