#include "BFLevel.h"
#include "../installers/BFLevelContext.h"

namespace BlackFox
{
	BFLevel::BFLevel(DiContainer container) : m_container(container)
	{
	}

	EntityManager BFLevel::entityManager() const
	{
		return m_entityManager;
	}

	BFLevel::Ptr BFLevel::create(DiContainer parentContainer)
	{
		//Make a copy of the parent container to have the same bindings + bindings only for the level
		const auto& c = *parentContainer.get();
		auto levelContainer = std::make_shared<cinject::Container>(c);
		levelContainer->bind<cinject::Container>().toConstant(levelContainer);

		//Level
		auto level = std::make_shared<BFLevel>(levelContainer);

		//Level context
		auto levelContext = makeContext<BFLevelContext, BFLevel::Ptr>(levelContainer, level);

		return level;
	}
}
