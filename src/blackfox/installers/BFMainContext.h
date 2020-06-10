#pragma once

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
	class BLACKFOX_EXPORT BFMainContext final : public BFBaseContext
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