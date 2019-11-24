#ifndef BLACKFOX_LEVELCONTEXT_H
#define BLACKFOX_LEVELCONTEXT_H

#include "BFBaseContext.h"
#include "../core/BFLevel.h"

namespace BlackFox
{
	/*!
	 * \class	BFLevelContext
	 *
	 * \brief	BlackFox level context.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFLevelContext : public BFBaseContext
	{
	public:
		/*!
		 * \fn	explicit BFLevelContext::BFLevelContext(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFLevelContext(DiContainer container, BFLevel::Ptr level);

		void init() override;

	private:
		BFLevel::Ptr m_level;
	};
}

#endif