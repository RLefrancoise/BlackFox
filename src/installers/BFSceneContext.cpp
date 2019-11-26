#include "BFSceneContext.h"
#include "BFSceneInstaller.h"

namespace BlackFox
{
	BFSceneContext::BFSceneContext(DiContainer container, BFScene::Ptr level) : BFBaseContext(container), m_level(level)
	{
	}

	void BFSceneContext::init()
	{
		addInstaller(std::make_shared<BFSceneInstaller>(m_container, m_level));
	}
}
