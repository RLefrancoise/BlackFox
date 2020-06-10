#include "BFCreateDefaultWorldService.h"

#include <rttr/type.h>

#include "BFApplication.h"
#include "BFWorld.h"
#include "BFComponentSystem.h"

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

        //Auto create systems
        auto systems = rttr::type::get<BFComponentSystem>().get_derived_classes();
        for(const auto& s : systems)
        {
            defaultWorld->createSystemFromType(s, m_application);
        }
    }
}