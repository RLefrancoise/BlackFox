#include "BFScriptingInstaller.h"
#include "BFLuaRuntimeRegistry.h"

namespace BlackFox
{
	BFScriptingInstaller::BFScriptingInstaller(DiContainer container) 
	: BFBaseInstaller(std::move(container))
	{}

	void BFScriptingInstaller::installBindings()
	{
		m_container->bind<BFLuaRuntimeRegistry>().toSelf().inSingletonScope();
	}
}