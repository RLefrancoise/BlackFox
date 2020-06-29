#include "BFCreateDefaultWorldService.h"

#include <rttr/type.h>

#include "BFApplication.h"
#include "BFWorld.h"

//#include "BFPhysicsSystem.h"
//#include "BFRenderSystem.h"

//using namespace BlackFox::Systems;

namespace BlackFox
{
    BFCreateDefaultWorldService::BFCreateDefaultWorldService(
        BFApplication::Ptr application,
        DiContainer container)
        : IBFApplicationService(std::move(application))
        , m_container(std::move(container))
        {}

    void BFCreateDefaultWorldService::run()
    {
        BF_PRINT("Run create default world service");

        //Create default world
        auto defaultWorld = BFWorld::create("default", m_container);

        //Create systems
        //defaultWorld->createSystem<BFRenderSystem>(BFRenderSystem::group, m_application);
        //defaultWorld->createSystem<BFPhysicsSystem>(BFPhysicsSystem::group, m_application);

        //Auto create systems
        auto systems = rttr::type::get<BFComponentSystem>().get_derived_classes();
        for(const auto& s : systems)
        {
            defaultWorld->createSystemFromType(s, m_application);
        }

        /*entt::resolve([&](entt::meta_type t)
        {
            auto base = t.base("ComponentSystem"_hs);
            if(base)
            {
                defaultWorld->createSystemFromType(t, m_application);
            }
        });*/


    }
}