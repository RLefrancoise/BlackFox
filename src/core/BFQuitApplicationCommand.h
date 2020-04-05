#ifndef BLACKFOX_QUITAPPLICATIONCOMMAND_H
#define BLACKFOX_QUITAPPLICATIONCOMMAND_H

#include <cinject/cinject.h>
#include <memory>
#include "common/BFCommand.h"

namespace BlackFox
{
	class BFApplication;

	class BFQuitApplicationCommand final : public BFCommand
	{
	private:
		std::shared_ptr<BFApplication> m_application;

	public:
		CINJECT(BFQuitApplicationCommand(std::shared_ptr<BFApplication> application));

		void execute(void) override;
		[[nodiscard]] BFQuitApplicationCommand* clone(void) const override;
	};
}

#endif