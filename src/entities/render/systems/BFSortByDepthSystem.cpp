#include "BFSortByDepthSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFDepthComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFSortByDepthSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	BFSortByDepthSystem::BFSortByDepthSystem(BFApplication::Ptr application)
	: BFComponentSystem(std::move(application))
	{}

	void BFSortByDepthSystem::update(float dt)
	{
		m_world->entityManager()->sort<BFDepthComponent>([](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.depth < rhs.depth;
		});
	}
}