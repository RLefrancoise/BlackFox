#include "BFCoreInstaller.h"

#include "BFCommandManager.h"
#include "BFApplication.h"
#include "BFEngineConfig.h"
#include "BFVirtualFileSystem.h"

#include "BFQuitApplicationCommand.h"

#include "BFDebug.h"
#include "BFResourcesHolder.h"

namespace BlackFox
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFCoreInstaller::installBindings()
	{
		try
		{
			//Config data
			/*auto holder = m_container->get<IBFResourcesHolder>();
			auto handle = holder->loadTextAsset("data/config.ini");
			auto configFile = BFIniFile(handle);
			configFile.loadOrThrow();*/

			auto engineConfig = std::make_shared<BFEngineConfig>(BFIniFile("config/engine.ini"));
			BF_PRINT(*engineConfig);
			m_container->bind<BFEngineConfig>().toConstant(engineConfig);

			//VFS
			m_container->bind<IBFVirtualFileSystem>().to<BFVirtualFileSystem>().inSingletonScope();

			//Resources holder
			m_container->bind<IBFResourcesHolder>().to<BFResourcesHolder>().inSingletonScope();

			//Command manager
			m_container->bind<BFCommandManager>().toSelf().inSingletonScope();

			//Commands
			m_container->bind<BFQuitApplicationCommand>().toSelf();

			//Application
			m_container->bind<BFApplication>().toSelf().inSingletonScope();
		}
		catch(std::exception& err)
		{
			BF_ERROR("{}", err.what());
		}


	}
}
