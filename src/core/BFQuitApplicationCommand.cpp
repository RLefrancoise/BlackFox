#include "BFQuitApplicationCommand.h"
#include "BFApplication.h"

namespace BlackFox
{
	BFQuitApplicationCommand::BFQuitApplicationCommand(BFApplication::Ptr application)
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