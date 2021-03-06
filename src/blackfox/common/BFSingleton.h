#ifndef BLACKFOX_SINGLETON_H
#define BLACKFOX_SINGLETON_H

#include "BFNonCopyable.h"

namespace BlackFox
{
	/*!
	 * \class	BFSingleton
	 *
	 * \brief	BlackFox Singleton template
	 *
	 * \author	Renaud Lefrançoise
	 * \date	13/11/2019
	 *
	 * \tparam	T	Class type to be templated
	 */
	template<class T>
	class BFSingleton : public BFNonCopyable
	{
	public:

		/*!
		 * \fn	static T& BFSingleton::get()
		 *
		 * \brief	Gets the singleton instance
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 *
		 * \returns	The singleton instance
		 */
		static T& get()
		{
			static T instance;
			return instance;
		}
	};
}

#endif