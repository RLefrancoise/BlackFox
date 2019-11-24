#include "BFCoreInstaller.h"
#include "../core/BFQuitApplicationCommand.h"

namespace BlackFox
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container) : BFBaseInstaller(container)
	{
	}

	void BFCoreInstaller::installBindings()
	{
		//Command manager
		m_container->bind<BFCommandManager>().toSelf().inSingletonScope();
		//Application
		m_container->bind<BFApplication>().toSelf().inSingletonScope();

		//Commands
		m_container->bind<BFQuitApplicationCommand>().toSelf();
	}
}
