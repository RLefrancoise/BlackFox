#include "BFSortByDepthSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFDepthComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFSortByDepthSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	struct DepthComparer
	{
		bool operator()(const BFDepthComponent& lhs, const BFDepthComponent& rhs) const
		{
			return lhs.depth < rhs.depth;
		}
	};
	
	void sortDepth(entt::entity e, entt::registry& r, BFDepthComponent& c)
	{
		r.sort<BFDepthComponent>([](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.depth < rhs.depth;
		});
	}

	BFSortByDepthSystem::BFSortByDepthSystem(BFApplication::Ptr application)
	: BFComponentSystem(std::move(application))
	{
		/*m_world->entityManager()->on_construct<BFDepthComponent>().connect<&sortDepth>();
		m_world->entityManager()->on_replace<BFDepthComponent>().connect<&sortDepth>();*/
	}

	BFSortByDepthSystem::~BFSortByDepthSystem()
	{
		/*m_world->entityManager()->on_construct<BFDepthComponent>().disconnect<&sortDepth>();
		m_world->entityManager()->on_replace<BFDepthComponent>().disconnect<&sortDepth>();*/
	}

	void BFSortByDepthSystem::update(float dt)
	{
		/*auto group = m_world->entityManager()->group(entt::get<BFDepthComponent>);
		//group.sort<const BFDepthComponent, DepthComparer>(DepthComparer());
		group.sort([&](const entt::entity lhs, const entt::entity rhs)
		{
			return group.get<BFDepthComponent>(lhs).depth < group.get<BFDepthComponent>(rhs).depth;
		});*/
	}
}