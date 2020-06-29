#include "BFUpdateViewSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFConfigData.h"

#include "BFViewComponent.h"
#include "BFTransformComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFUpdateViewSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
    BFUpdateViewSystem::BFUpdateViewSystem(BFApplication::Ptr app, BFWorld::Ptr world)
    : BFComponentSystem(std::move(app), std::move(world))
    {}

    void BFUpdateViewSystem::update(float dt)
    {
        auto views = m_world->entityManager()->view<BFViewComponent, const BFTransformComponent>();
        const auto gameData = m_application->configData()->gameData;

        views.each([&](const entt::entity e, BFViewComponent& view, const BFTransformComponent& transform)
        {
            view.m_view.setCenter(gameData.worldToPixels(transform.position));
            view.m_view.setSize(gameData.worldToPixels(view.size));
            view.m_view.setViewport(view.viewport);
        });
    }
}