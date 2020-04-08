#include "BFCoreInstaller.h"

#include "core/BFEditorApplication.h"
#include "BFCommandManager.h"
#include "core/BFQuitEditorCommand.h"
#include "windows/BFMenuBar.h"

namespace BlackFox::Editor
{
	BFCoreInstaller::BFCoreInstaller(DiContainer container)
	: BFBaseInstaller(std::move(container))
	{
	}

	void BFCoreInstaller::installBindings()
	{
		m_container->bind<BFEditorApplication>().toSelf().inSingletonScope();
		m_container->bind<BFCommandManager>().toSelf().inSingletonScope();

		m_container->bind<BFQuitEditorCommand>().toSelf();
	}

}
