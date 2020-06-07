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
		constexpr explicit BFDegree(float degrees = 0.f)
		: m_value(degrees)
		{}

		constexpr BFDegree(const BFDegree& degree) = default;
		constexpr BFDegree(BFDegree&& degree) noexcept = default;

		BFDegree& operator=(const BFDegree&) = default;
		BFDegree& operator=(BFDegree&&) noexcept = default;

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
		[[nodiscard]] constexpr float value() const { return m_value; }

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

		constexpr operator float() const
		{
			return m_value;
		}

		operator BFRadian() const;

	private:
		/*! \brief	The number of degrees. */
		float m_value;
	};
}

#endif