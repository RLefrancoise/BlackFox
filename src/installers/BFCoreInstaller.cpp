#include "BFCoreInstaller.h"

#include "BFCommandManager.h"
#include "BFApplication.h"
#include "BFScriptingManager.h"

#include "BFQuitApplicationCommand.h"

namespace BlackFox
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFCoreInstaller::installBindings()
	{
		//Command manager
		m_container->bind<BFCommandManager>().toSelf().inSingletonScope();
		//Application
		m_container->bind<BFApplication>().toSelf().inSingletonScope();
		//Scripting manager
		m_container->bind<BFScriptingManager>().toSelf().inSingletonScope();

		//Commands
		m_container->bind<BFQuitApplicationCommand>().toSelf();
	}
}
