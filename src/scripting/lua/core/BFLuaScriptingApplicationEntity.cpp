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
        application_type["renderer"] = &BFApplication::renderer;
        application_type["config_data"] = &BFApplication::configData;
    }
}
