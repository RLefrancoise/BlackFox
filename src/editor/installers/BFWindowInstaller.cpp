#include "BFWindowInstaller.h"

#include "windows/BFMenuBar.h"

namespace BlackFox::Editor
{
	BFWindowInstaller::BFWindowInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFWindowInstaller::installBindings()
	{
		m_container->bind<BFMenuBar>().toSelf().inSingletonScope();
	}
}
