#ifndef BLACKFOX_DEGREE_H
#define BLACKFOX_DEGREE_H

namespace BlackFox
{
	class BFRadian;

	/*!
	 * \class	BFDegree
	 *
	 * \brief	BlackFox Degree class. Can be converted to Radian.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	11/11/2019
	 */
	class BFDegree
	{
	public:

		/*!
		 * \fn	explicit BFDegree::BFDegree(float degrees = 0.f);
		 *
		 * \brief	Constructor.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	degrees	(Optional) Initial degrees.
		 */
		explicit BFDegree(float degrees = 0.f);

		/*!
		 * \fn	explicit BFDegree::BFDegree(const BFRadian& radians);
		 *
		 * \brief	Constructor.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	radians	The radians to be converted to degrees.
		 */
		explicit BFDegree(const BFRadian& radians);

		/*!
		 * \fn	float BFDegree::value() const;
		 *
		 * \brief	Gets the degrees value.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	Number of degrees.
		 */
		float value() const;

		/*!
		 * \fn	BFDegree BFDegree::operator=(const BFRadian& radians) const;
		 *
		 * \brief	Assign a Radian object to this Degree object by converting the value.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	radians	The Radians object to assign.
		 *
		 * \returns	A Degree object with the converted value.
		 */
		BFDegree& operator=(const BFRadian& radians);

		BFDegree& operator=(float angle);

		float operator()();

	private:
		/*! \brief	The number of degrees. */
		float m_value;
	};
}

#endif