#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox
{
	class BLACKFOX_EXPORT BFEntitiesInstaller final : public BFBaseInstaller
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