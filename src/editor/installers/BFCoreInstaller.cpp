#include "BFCoreInstaller.h"

#include "BFEditorApplication.h"
#include "BFCommandManager.h"
#include "BFDataManager.h"
#include "BFWindowManager.h"

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
		m_container->bind<BFWindowManager>().toSelf().inSingletonScope();
		m_container->bind<BFDataManager>().toSelf().inSingletonScope();
	}

}
