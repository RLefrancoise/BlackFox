#pragma once

#include <string>
#include <fmt/format.h>
#include <SFML/System/Vector2.hpp>

#include "Box2D/Common/b2Math.h"
#include "BFExport.h"

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
    template <typename T>
	struct BLACKFOX_EXPORT BFVector2
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
		constexpr explicit BFVector2(T x = 0, T y = 0)
		: x(x)
		, y(y)
		{}

		constexpr BFVector2(const BFVector2<T>& v) = default;

		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	01/12/2019
		 *
		 * \param	v	The SDL vector.
		 */
		constexpr explicit BFVector2(const sf::Vector2<T>& v)
		: x(v.x)
		, y(v.y)
		{}
    	
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
		constexpr BFVector2<T> operator+(const BFVector2<T>& rhs) const
		{
			return BFVector2<T>(x + rhs.x, y + rhs.y);
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
		constexpr BFVector2<T> operator-(const BFVector2<T>& rhs) const
		{
			return BFVector2<T>(x - rhs.x, y - rhs.y);
		}

		/*!
		 * \brief	Negates this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	The new vector
		 */
		constexpr BFVector2<T> operator-() const
		{
			return BFVector2<T>(-x, -y);
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
		constexpr BFVector2<T> operator*(float scale) const
		{
			return BFVector2<T>(x * scale, y * scale);
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
		BFVector2<T>& operator+(const BFVector2<T>& rhs)
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
		BFVector2<T>& operator-(const BFVector2<T>& rhs)
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
		BFVector2<T>& operator-()
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
		BFVector2<T>& operator*(float scale)
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
		constexpr bool operator==(const BFVector2<T>& rhs) const
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
		constexpr bool operator!=(const BFVector2<T>& rhs) const
		{
			return !(*this == rhs);
		}

		constexpr BFVector2<T>& operator=(const BFVector2<T>& v) = default;
		constexpr BFVector2<T>& operator=(BFVector2<T>&& v) noexcept = default;

		BFVector2<T>& operator=(const sf::Vector2<T>& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		BFVector2<T>& operator=(sf::Vector2<T>&& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		constexpr operator sf::Vector2<T> () const { return sf::Vector2<T>(x, y); }

		explicit operator std::string() const { return fmt::format("({},{})", x, y); }
    	
		/*! \brief	X value */
		T x;
		/*! \brief	Y value */
		T y;
	};

	typedef BFVector2<float> BFVector2f;
    typedef BFVector2<int> BFVector2i;
	typedef BFVector2<unsigned int> BFVector2u;
    typedef BFVector2<double> BFVector2d;
	
	/**
	 * \brief	Construct a BFVector2f from a string: xx.xx,xx.xx
	 * \param	str	The formatted string
	 * 
	 * \return	The BFVector2f vector
	 */
	BLACKFOX_EXPORT BFVector2f vector2fFromString(const std::string& str);
}