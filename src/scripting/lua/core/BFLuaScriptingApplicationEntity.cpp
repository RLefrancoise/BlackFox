#include "BFLuaScriptingApplicationEntity.h"
#include "BFApplication.h"
#include "BFCommandManager.h"
#include "BFConfigData.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingApplicationEntity, "Application")

namespace BlackFox
{
    void BFLuaScriptingApplicationEntity::registerEntity()
    {
        sol::usertype <BFApplication> application_type = m_namespace.new_usertype<BFApplication>("Application");
        application_type["quit"] = &BFApplication::quit;
        application_type["command_manager"] = &BFApplication::commandManager;
        application_type["window"] = &BFApplication::window;
        application_type["config_data"] = &BFApplication::configData;

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

        screenNs["worldToPixels"] = [&](float x, float y) -> BFVector2f
        {
            const auto& app = m_container->get<BFApplication>();
            return app->configData()->gameData.worldToPixels(x, y);
        };

		screenNs["pixelsToWorld"] = [&](float x, float y) -> BFVector2f
		{
			const auto& app = m_container->get<BFApplication>();
			return app->configData()->gameData.pixelsToWorld(x, y);
		};
    }
}
