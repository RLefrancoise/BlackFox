#include "BFScriptingInstaller.h"
#include "BFLuaRuntimeRegistry.h"
#include "BFScriptingManager.h"

namespace BlackFox
{
	BFScriptingInstaller::BFScriptingInstaller(DiContainer container) 
	: BFBaseInstaller(std::move(container))
	{}

	void BFScriptingInstaller::installBindings()
	{
		//Scripting manager
		m_container->bind<BFScriptingManager>().toSelf().inSingletonScope();

		m_container->bind<BFLuaRuntimeRegistry>().toSelf().inSingletonScope();
	}
}