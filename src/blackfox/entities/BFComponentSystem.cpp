#include "BFComponentSystem.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFComponentSystemMacros.h"

#ifdef BLACKFOX_SHARED_LIB

RTTR_PLUGIN_REGISTRATION
{
	using namespace rttr;
	registration::class_<BlackFox::BFComponentSystem>("ComponentSystem")
	.method("update", &BlackFox::BFComponentSystem::update);
}

#else

RTTR_REGISTRATION
{
	using namespace rttr;
	registration::class_<BlackFox::BFComponentSystem>("ComponentSystem")
	.method("update", &BlackFox::BFComponentSystem::update);
}

#endif

namespace BlackFox
{
	struct register_component_system
	{
		register_component_system()
		{
			entt::meta<BFComponentSystem>()
				.type("ComponentSystem"_hs);
		}
	};

	register_component_system register__;

	//------------------------------------------------------------------------

	/*BFComponentSystem::BFComponentSystem(const BFComponentSystem& system) = default;
	BFComponentSystem& BFComponentSystem::operator=(const BFComponentSystem& system) = default;*/

	BFComponentSystem::BFComponentSystem(BFComponentSystem&& system) noexcept
	{
		std::swap(m_application, system.m_application);
		std::swap(m_world, system.m_world);
	}

	BFComponentSystem& BFComponentSystem::operator=(BFComponentSystem&& system) noexcept
	{
		m_application = std::move(system.m_application);
		m_world = std::move(system.m_world);
		return *this;
	}

	BFComponentSystem::BFComponentSystem(BFApplication::Ptr application, BFWorld::Ptr world)
	: m_application(std::move(application))
	, m_world(std::move(world))
	{}
}