#include "BFScene.h"
#include "BFSceneContext.h"

namespace BlackFox
{
	BFScene::BFScene(DiContainer container)
	: m_container(std::move(container))
	{
	}

	BFScene::Ptr BFScene::create(DiContainer parentContainer)
	{
		//Create a scene container with main container as its parent to inherit the bindings
		cinject::Container* c = parentContainer.get();
		auto sceneContainer = std::make_shared<cinject::Container>(c);
		sceneContainer->bind<cinject::Container>().toConstant(sceneContainer);

		//Scene
		auto scene = std::make_shared<BFScene>(sceneContainer);

		//Scene context
		auto sceneContext = makeContext<BFSceneContext, BFScene::Ptr>(sceneContainer, scene);

		return scene;
	}
}
