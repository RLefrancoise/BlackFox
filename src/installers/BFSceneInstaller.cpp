#include "BFSceneInstaller.h"
#include "BFWorld.h"

namespace BlackFox
{
	BFSceneInstaller::BFSceneInstaller(DiContainer container, BFScene::Ptr level) : BFBaseInstaller(container), m_scene(level)
	{
	}

	void BFSceneInstaller::installBindings()
	{
		m_container->bind<BFScene>().toConstant(m_scene);
	}
}
