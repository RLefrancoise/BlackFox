#include "BFScene.h"
#include "BFSceneContext.h"

namespace BlackFox
{
	BFScene::BFScene(DiContainer container) : m_container(container)
	{
	}

	EntityManager BFScene::entityManager() const
	{
		return m_entityManager;
	}

	BFScene::Ptr BFScene::create(DiContainer parentContainer)
	{
		//Make a copy of the parent container to have the same bindings + bindings only for the level
		const auto& c = *parentContainer.get();
		auto levelContainer = std::make_shared<cinject::Container>(c);
		levelContainer->bind<cinject::Container>().toConstant(levelContainer);

		//Level
		auto level = std::make_shared<BFScene>(levelContainer);

		//Level context
		auto levelContext = makeContext<BFSceneContext, BFScene::Ptr>(levelContainer, level);

		return level;
	}
}
