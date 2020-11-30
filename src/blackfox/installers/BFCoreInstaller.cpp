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
			//Command manager
			m_container->bind<BFCommandManager>().toSelf().inSingletonScope();

			//Application
			m_container->bind<BFApplication>().toSelf().inSingletonScope();

			//VFS
			m_container->bind<IBFVirtualFileSystem>().to<BFVirtualFileSystem>().inSingletonScope();

			//Commands
			m_container->bind<BFQuitApplicationCommand>().toSelf();

			//Config data
			auto configFile = BFIniFile(Resources::ENGINE_CONFIG);
			configFile.loadOrThrow("data/config.ini");

			auto engineConfig = std::make_shared<BFEngineConfig>(configFile);
			BF_PRINT(*engineConfig);
			m_container->bind<BFEngineConfig>().toConstant(std::move(engineConfig));

			//Resources holder
			m_container->bind<IBFResourcesHolder>().to<BFResourcesHolder>().inSingletonScope();
		}
		catch(std::exception& err)
		{
			BF_ERROR("{}", err.what());
		}


	}
}
