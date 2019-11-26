#ifndef BLACKFOX_ENTITIESINSTALLER_H
#define BLACKFOX_ENTITIESINSTALLER_H

#include "BFBaseInstaller.h"

namespace BlackFox
{
	class BFEntitiesInstaller : public BFBaseInstaller
	{
	public:

		/*!
		 * \fn	explicit BFEntitiesInstaller::BFEntitiesInstaller(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	container	The container.
		 */
		explicit BFEntitiesInstaller(DiContainer container);

		void installBindings() override;
	};
}

#endif