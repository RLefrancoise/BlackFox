#include "BFCoreInstaller.h"
#include "../core/BFQuitApplicationCommand.h"

namespace BlackFox
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container) : BFBaseInstaller(container)
	{
	}

	void BFCoreInstaller::installBindings()
	{
		m_container->bind<BFCommandManager>().toSelf().inSingletonScope();
		m_container->bind<BFApplication>().toSelf().inSingletonScope();

		m_container->bind<BFQuitApplicationCommand>().toSelf();
	}
}
