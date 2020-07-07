#include "BFEntitiesModule.h"

#include "BFEntitiesInstaller.h"
#include "BFWorld.h"
#include "BFApplication.h"

namespace BlackFox::Entities
{
    BFEntitiesModule::BFEntitiesModule(DiContainer container)
    : BFApplicationModule(std::move(container))
    {}

    void BFEntitiesModule::install(const DiContext &context)
    {
        context->addInstaller(std::make_shared<BFEntitiesInstaller>(m_container));
    }

    void BFEntitiesModule::onUpdate(float dt)
    {
        BFApplicationModule::onUpdate(dt);

        auto worlds = BFWorld::all();
        for(const auto& w : worlds)
            w->refreshSystems(ComponentSystemGroups::GameLoop, dt);
    }

    void BFEntitiesModule::onFixedUpdate(float dt)
    {
        BFApplicationModule::onFixedUpdate(dt);

        auto worlds = BFWorld::all();
        for (const auto& w : worlds)
            w->refreshSystems(ComponentSystemGroups::FixedTime, dt);
    }

    void BFEntitiesModule::onRender(float dt)
    {
        BFApplicationModule::onRender(dt);

        auto worlds = BFWorld::all();
        for (const auto& w : worlds)
            w->refreshSystems(ComponentSystemGroups::Render, dt);
    }

    void BFEntitiesModule::onEndOfFrame(float dt)
    {
        BFApplicationModule::onEndOfFrame(dt);

        auto worlds = BFWorld::all();
        for (const auto& w : worlds)
            w->refreshSystems(ComponentSystemGroups::EndOfFrame, dt);
    }

    void BFEntitiesModule::onInit()
    {
        BFApplicationModule::onInit();

        BF_PRINT("Init entities module");

        //Get application
        auto application = m_container->get<BFApplication>();

        //Create default world
        auto defaultWorld = BFWorld::create("default", m_container);

        //Auto create systems
        auto systems = rttr::type::get<BFComponentSystem>().get_derived_classes();
        for(const auto& s : systems)
        {
            defaultWorld->createSystemFromType(s, application);
        }
    }
}
