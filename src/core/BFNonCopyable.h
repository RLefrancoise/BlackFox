#ifndef BLACKFOX_NONCOPYABLE_H
#define BLACKFOX_NONCOPYABLE_H

namespace BlackFox
{
	/*!
	 * \class	BFNonCopyable
	 *
	 * \brief	BlackFox Non Copyable class. Is meant to be private inherited to disallow a class to be copied.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	13/11/2019
	 */
	class BFNonCopyable
	{
	public:
		BFNonCopyable() = default;
		BFNonCopyable(const BFNonCopyable& app) = delete;
		BFNonCopyable& operator=(const BFNonCopyable& app) = delete;
		BFNonCopyable& operator=(BFNonCopyable&& app) = delete;
	};
}

#endif
