#include "BFSceneInstaller.h"
#include "BFWorld.h"

namespace BlackFox
{
	BFSceneInstaller::BFSceneInstaller(DiContainer container, BFScene::Ptr level)
	: BFBaseInstaller(std::move(container))
	, m_scene(std::move(level))
	{
	}

	void BFSceneInstaller::installBindings()
	{
		m_container->bind<BFScene>().toConstant(m_scene);
	}
}
