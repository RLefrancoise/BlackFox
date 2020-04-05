#ifndef BLACKFOX_MAINCONTEXT_H
#define BLACKFOX_MAINCONTEXT_H

#include "BFBaseContext.h"

namespace BlackFox
{
	/*!
	 * \class	BFMainContext
	 *
	 * \brief	BlackFox Main DI Context
	 *
	 * \author	Renaud Lefrançoise
	 * \date	22/11/2019
	 */
	class BFMainContext final : public BFBaseContext
	{
	public:

		/*!
		 * \fn	explicit BFMainContext::BFMainContext(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	22/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFMainContext(DiContainer container);

		void init() override;
	};
}

#endif