#ifndef BLACKFOX_QUITAPPLICATIONCOMMAND_H
#define BLACKFOX_QUITAPPLICATIONCOMMAND_H

#include <cinject/cinject.h>
#include <memory>
#include "BFCommand.h"
#include "BFApplication.h"

namespace BlackFox
{
	class BFQuitApplicationCommand : public BFCommand
	{
	private:
		std::shared_ptr<BFApplication> m_application;

	public:
		CINJECT(BFQuitApplicationCommand(std::shared_ptr<BFApplication> application));
		BFQuitApplicationCommand(const BFQuitApplicationCommand& cmd) {}

		void execute(void) override;
		BFQuitApplicationCommand* clone(void) const override;
	};
}

#endif