#include "BFEntitiesInstaller.h"
#include "BFWorld.h"

namespace BlackFox
{
	BFEntitiesInstaller::BFEntitiesInstaller(DiContainer container) : BFBaseInstaller(container)
	{
	}

	void BFEntitiesInstaller::installBindings()
	{
		//Creates a new world each time get is called
		m_container->bind<BFWorld>().toSelf();
	}
}
