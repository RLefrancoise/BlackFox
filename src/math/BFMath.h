#ifndef BLACKBOX_MATH_H
#define BLACKFOX_MATH_H

namespace BlackFox
{
	namespace BFMath
	{
		/*! \brief	The smallest value between two floats. */
		const float EPSILON = 0.00001f;
		/*! \brief	The value of PI. */
		const float PI = 3.1415926535897932384626433832795f;
		/*! \brief	The value of PI/2. */
		const float HALF_PI = PI * 0.5f;
		/*! \brief	The value of 2PI. */
		const float TWO_PI = PI * 2.0f;

		/*!
		 * \fn	float clamp(float x, float low, float high);
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
		float clamp(float x, float low, float high);

		/*!
		 * \fn	float wrap(float x, float low, float high);
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
		float wrap(float x, float low, float high);

		/*!
		 * \fn	float min(float first, float second);
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
		float min(float first, float second);

		/*!
		 * \fn	float max(float first, float second);
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
		float max(float first, float second);

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
	}
}

#endif
