#include "BFQuitApplicationCommand.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFQuitApplicationCommand::BFQuitApplicationCommand(std::shared_ptr<BFApplication> application)
	: m_application(std::move(application))
	{
	}

	void BFQuitApplicationCommand::execute(void)
	{
		BF_PRINT("Quit application")
		m_application->quit();
	}

	BFQuitApplicationCommand* BFQuitApplicationCommand::clone(void) const
	{
		return new BFQuitApplicationCommand(m_application);
	}
}