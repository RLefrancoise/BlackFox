#include "BFWindowInstaller.h"

#include "BFSceneListWindow.h"
#include "windows/BFMenuBar.h"
#include "BFWindowManager.h"

namespace BlackFox::Editor
{
	BFWindowInstaller::BFWindowInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFWindowInstaller::installBindings()
	{
		m_container->bind<BFMenuBar>().toSelf().inSingletonScope();
		m_container->bind<BFSceneListWindow>().toSelf().inSingletonScope();
	}
}
