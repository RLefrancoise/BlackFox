#ifndef BLACKFOX_VECTOR2_H
#define BLACKFOX_VECTOR2_H

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
		 * \fn	explicit BFVector2(float x = 0, float y = 0);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	x	(Optional) The x value.
		 * \param	y	(Optional) The y value.
		 */
		explicit BFVector2(float x = 0, float y = 0);

		/*!
		 * \fn	BFVector2 operator+(const BFVector2& rhs) const;
		 *
		 * \brief	Adds a vector to this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to add
		 *
		 * \returns	The new vector
		 */
		BFVector2 operator+(const BFVector2& rhs) const;

		/*!
		 * \fn	BFVector2 operator-(const BFVector2& rhs) const;
		 *
		 * \brief	Substract a vector from this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to substract
		 *
		 * \returns	The new vector
		 */
		BFVector2 operator-(const BFVector2& rhs) const;

		/*!
		 * \fn	BFVector2 operator-(void) const;
		 *
		 * \brief	Negates this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	The new vector
		 */
		BFVector2 operator-(void) const;

		/*!
		 * \fn	BFVector2 operator*(float scale) const;
		 *
		 * \brief	Scales this vector and returns a new vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	scale	The scale factor.
		 *
		 * \returns	The new vector.
		 */

		BFVector2 operator*(float scale) const;

		/*!
		 * \fn	BFVector2& operator+(const BFVector2& rhs);
		 *
		 * \brief	Adds a vector to this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to add
		 *
		 * \returns	The updated vector
		 */
		BFVector2& operator+(const BFVector2& rhs);

		/*!
		 * \fn	BFVector2& operator-(const BFVector2& rhs);
		 *
		 * \brief	Substract a vector from this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	rhs	The vector to substract
		 *
		 * \returns	The updated vector.
		 */
		BFVector2& operator-(const BFVector2& rhs);

		/*!
		 * \fn	BFVector2& operator-(void);
		 *
		 * \brief	Negates this vector
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	The updated vector
		 */
		BFVector2& operator-(void);

		/*! \brief	X value */
		float x;
		/*! \brief	Y value */
		float y;
	};
}

#endif