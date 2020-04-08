#include "BFCoreInstaller.h"

#include "BFEditorApplication.h"

namespace BlackFox::Editor
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFCoreInstaller::installBindings()
	{
		m_container->bind<BFEditorApplication>().toSelf().inSingletonScope();
	}

}
