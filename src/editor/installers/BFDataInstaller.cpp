#include "BFDataInstaller.h"
#include "BFEditorResourcesHolder.h"

namespace BlackFox::Editor
{
	BFDataInstaller::BFDataInstaller(DiContainer container) : BFBaseInstaller(std::move(container))
	{
	}

	void BFDataInstaller::installBindings()
	{
		m_container->bind<IBFResourcesHolder>().to<BFEditorResourcesHolder>().inSingletonScope();
	}
}
