#include "BFWindowInstaller.h"

#include "BFDataBrowserWindow.h"
#include "BFLoadProjectWindow.h"
#include "BFNewProjectWindow.h"
#include "BFSceneListWindow.h"
#include "BFMenuBar.h"
#include "BFSettingsWindow.h"

namespace BlackFox::Editor
{
	BFWindowInstaller::BFWindowInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFWindowInstaller::installBindings()
	{
		m_container->bind<BFLoadProjectWindow>().toSelf().inSingletonScope();
		m_container->bind<BFMenuBar>().toSelf().inSingletonScope();
		m_container->bind<BFMessagePopup>().toSelf().inSingletonScope();
		m_container->bind<BFNewProjectWindow>().toSelf().inSingletonScope();
		
		m_container->bind<BFSettingsWindow>().toSelf().inSingletonScope();

		m_container->bind<BFSceneListWindow>().toSelf().inSingletonScope();
		m_container->bind<BFDataBrowserWindow>().toSelf().inSingletonScope();
	}
}
