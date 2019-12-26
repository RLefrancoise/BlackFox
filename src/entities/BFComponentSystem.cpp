#include "BFComponentSystem.h"
#include "BFWorld.h"
#include "BFApplication.h"
#include "BFComponentSystemMacros.h"

RTTR_REGISTRATION
{
	using namespace rttr;
	registration::class_<BlackFox::BFComponentSystem>("ComponentSystem")
	.method("update", &BlackFox::BFComponentSystem::update)
	.method("setWorld",&BlackFox::BFComponentSystem::setWorld);
}

namespace BlackFox
{
	BFComponentSystem::BFComponentSystem(BFApplication *application)
	: m_application(application)
	, m_world(nullptr)
	{
	}

	BFComponentSystem::BFComponentSystem(BFApplication::Ptr application)
	: m_application(application.get())
	, m_world(nullptr)
	{
	}

	void BFComponentSystem::setWorld(BFWorld* world)
	{
		m_world = world;
	}
}