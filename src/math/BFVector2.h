#ifndef BLACKFOX_VECTOR2_H
#define BLACKFOX_VECTOR2_H

#include <cpp-sdl2/vec2.hpp>

namespace BlackFox
{
	/*!
	 * \struct	BFVector2
	 *
	 * \brief	BlackFox Vector2 class
	 *
	 * \author	Renaud Lefrançoise
	 * \date	11/11/2019
	 */

	struct BFVector2
	{
		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	x	(Optional) The x value.
		 * \param	y	(Optional) The y value.
		 */
		constexpr explicit BFVector2(float x = 0, float y = 0)
		: x(x)
		, y(y)
		{}

		constexpr BFVector2(const BFVector2& v) = default;

		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	01/12/2019
		 *
		 * \param	v	The SDL vector.
		 */
		constexpr explicit BFVector2(const sdl::Vec2f& v)
		: x(v.x)
		, y(v.y)
		{
		}

		/*!
		 * \brief	Adds a vector to this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to add
		 *
		 * \returns	The new vector
		 */
		constexpr BFVector2 operator+(const BFVector2& rhs) const
		{
			return BFVector2(x + rhs.x, y + rhs.y);
		}

		/*!
		 * \brief	Substract a vector from this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to substract
		 *
		 * \returns	The new vector
		 */
		constexpr BFVector2 operator-(const BFVector2& rhs) const
		{
			return BFVector2(x - rhs.x, y - rhs.y);
		}

		/*!
		 * \brief	Negates this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	The new vector
		 */
		constexpr BFVector2 operator-() const
		{
			return BFVector2(-x, -y);
		}

		/*!
		 * \brief	Scales this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	scale	The scale factor.
		 *
		 * \returns	The new vector.
		 */
		constexpr BFVector2 operator*(float scale) const
		{
			return BFVector2(x * scale, y * scale);
		}

		/*!
		 * \brief	Adds a vector to this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to add
		 *
		 * \returns	The updated vector
		 */
		constexpr BFVector2& operator+(const BFVector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		/*!
		 * \brief	Substract a vector from this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to substract
		 *
		 * \returns	The updated vector.
		 */
		constexpr BFVector2& operator-(const BFVector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		/*!
		 * \brief	Negates this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	The updated vector
		 */
		constexpr BFVector2& operator-()
		{
			x = -x;
			y = -y;
			return *this;
		}

		/*!
		 * \brief	Scale this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	scale	The scale factor.
		 *
		 * \returns	The updated vector.
		 */
		constexpr BFVector2& operator*(float scale)
		{
			x *= scale;
			y *= scale;
			return *this;
		}

		/*!
		 * \brief	Tests if this vector is equals to another vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The other vector
		 *
		 * \returns	True if the vector is equal to the other vector
		 */
		constexpr bool operator==(const BFVector2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		/*!
		 * \brief	Tests if this vector is not equal to another vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The other vector
		 *
		 * \returns	True if the vector is not equal to the other vector
		 */
		constexpr bool operator!=(const BFVector2& rhs) const
		{
			return !(*this == rhs);
		}

		constexpr BFVector2& operator=(const BFVector2& v) = default;
		constexpr BFVector2& operator=(BFVector2&& v) = default;

		constexpr BFVector2& operator=(const sdl::Vec2f& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		constexpr BFVector2& operator=(sdl::Vec2f&& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		constexpr operator sdl::Vec2f () const { return sdl::Vec2f(x, y); }

		/*! \brief	X value */
		float x;
		/*! \brief	Y value */
		float y;
	};
}

#endif