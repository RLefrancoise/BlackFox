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
	/*BFComponentSystem::BFComponentSystem(BFApplication *application)
	: m_application(application)
	, m_world(nullptr)
	{
	}*/

	BFComponentSystem::BFComponentSystem(BFComponentSystem&& system) noexcept
	: m_application(system.m_application)
	, m_world(system.m_world)
	{
	}

	BFComponentSystem& BFComponentSystem::operator=(BFComponentSystem&& system) noexcept
	{
		m_application = system.m_application;
		m_world = system.m_world;
		return *this;
	}

	BFComponentSystem::BFComponentSystem(BFApplication::Ptr application, BFWorld::Ptr world)
	: m_application(std::move(application))
	, m_world(std::move(world))
	{
	}

	/*void BFComponentSystem::setWorld(BFWorld::Ptr world)
	{
		m_world = std::move(world);
	}*/
}