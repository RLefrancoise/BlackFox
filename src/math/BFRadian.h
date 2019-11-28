#ifndef BLACKFOX_RADIAN_H
#define BLACKFOX_RADIAN_H

namespace BlackFox
{
	class BFDegree;

	/*!
	 * \class	BFRadian
	 *
	 * \brief	BlackFox Radian class. Can be converted to Degree.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	11/11/2019
	 */
	class BFRadian
	{
	public:

		/*!
		 * \fn	explicit BFRadian::BFRadian(float radians = 0.f);
		 *
		 * \brief	Constructor.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	radians	(Optional) Initial radians.
		 */
		explicit BFRadian(float radians = 0.f);

		/*!
		 * \fn	explicit BFRadian::BFRadian(const BFDegree& degrees);
		 *
		 * \brief	Constructor.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	degrees	The degrees to be converted to radians.
		 */
		explicit BFRadian(const BFDegree& degrees);

		/*!
		 * \fn	float BFRadian::value() const;
		 *
		 * \brief	Gets the radian value.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \returns	Number of radians
		 */
		float value() const;

		/*!
		 * \fn	BFRadian& BFRadian::operator=(const BFDegree& degrees);
		 *
		 * \brief	Assign a Degree object to this Radian object by converting the value.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	11/11/2019
		 *
		 * \param	degrees	The Degree object to assign.
		 *
		 * \returns	A Radian object with the converted value.
		 */
		BFRadian& operator=(const BFDegree& degrees);

	private:
		/*! \brief	The number of radians. */
		float m_value;
	};
}

#endif