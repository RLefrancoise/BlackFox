#include "BFLuaScriptingApplicationEntity.h"
#include "BFApplication.h"
#include "BFCommandManager.h"
#include "BFConfigData.h"
#include <sol/property.hpp>
#include <sol/overload.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingApplicationEntity, "Application")

namespace BlackFox
{
    void BFLuaScriptingApplicationEntity::registerEntity()
    {
	    auto applicationType = m_namespace.new_usertype<BFApplication>("Application");
        applicationType["quit"] = &BFApplication::quit;
        applicationType["command_manager"] = &BFApplication::commandManager;
        applicationType["window"] = &BFApplication::window;
        applicationType["config_data"] = &BFApplication::configData;

        //Screen
        auto screenNs = m_namespace["Screen"].get_or_create<sol::table>();
        screenNs["width"] = sol::readonly_property([&]() -> sf::Uint32
        {
            const auto& app = m_container->get<BFApplication>();
            return app->window()->getSize().x;
        });

		screenNs["height"] = sol::readonly_property([&]() -> sf::Uint32
		{
			const auto& app = m_container->get<BFApplication>();
			return app->window()->getSize().y;
		});

        screenNs["worldToPixels"] = sol::overload(
        [&](float x, float y) -> BFVector2f
        {
            const auto& app = m_container->get<BFApplication>();
            return app->configData()->gameData.worldToPixels(x, y);
        },
        [&](const float value) -> float
        {
            const auto& app = m_container->get<BFApplication>();
            return app->configData()->gameData.worldToPixels(value);
        });

		screenNs["pixelsToWorld"] = sol::overload(
		[&](float x, float y) -> BFVector2f
		{
			const auto& app = m_container->get<BFApplication>();
			return app->configData()->gameData.pixelsToWorld(x, y);
		},
		[&](const float value) -> float
		{
            const auto& app = m_container->get<BFApplication>();
            return app->configData()->gameData.pixelsToWorld(value);
		});
    }
}
