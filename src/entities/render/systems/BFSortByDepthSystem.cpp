#include "BFSortByDepthSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFDepthComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFSortByDepthSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
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
		m_world->entityManager()->on_construct<BFDepthComponent>().connect<&sortDepth>();
		m_world->entityManager()->on_replace<BFDepthComponent>().connect<&sortDepth>();
	}

	BFSortByDepthSystem::~BFSortByDepthSystem()
	{
		m_world->entityManager()->on_construct<BFDepthComponent>().disconnect<&sortDepth>();
		m_world->entityManager()->on_replace<BFDepthComponent>().disconnect<&sortDepth>();
	}

	void BFSortByDepthSystem::update(float dt)
	{
		auto group = m_world->entityManager()->group(entt::get<const BFDepthComponent>);
		group.sort<const BFDepthComponent>([](const BFDepthComponent& left, const BFDepthComponent& right)
		{
			return left.depth < right.depth;
		});
	}
}