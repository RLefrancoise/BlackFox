#ifndef BLACKFOX_QUITAPPLICATIONCOMMAND_H
#define BLACKFOX_QUITAPPLICATIONCOMMAND_H

#include <cinject/cinject.h>
#include <memory>
#include "common/IBFCommand.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	class BFApplication;

	class BLACKFOX_EXPORT BFQuitApplicationCommand final : public BFCommandBase<BFQuitApplicationCommand>
	{
	private:
		std::shared_ptr<BFApplication> m_application;

	public:
		CINJECT(BFQuitApplicationCommand(std::shared_ptr<BFApplication> application));

		void execute();
		[[nodiscard]] BFQuitApplicationCommand* clone(void) const override;
	};
}

#endif