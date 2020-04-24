#include "BFDataInstaller.h"

#include "BFResourcesHolder.h"

namespace BlackFox::Editor
{
	BFDataInstaller::BFDataInstaller(DiContainer container) : BFBaseInstaller(std::move(container))
	{
	}

	void BFDataInstaller::installBindings()
	{
		m_container->bind<BFResourcesHolder>().toSelf().inSingletonScope();
	}
}
