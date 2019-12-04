#include "BFLuaScriptingInputEntity.h"
#include "BFInput.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingInputEntity, "Input")

namespace BlackFox
{
    void BFLuaScriptingInputEntity::registerEntity()
    {
        sol::table input = m_namespace["Input"].get_or_create<sol::table>();
        sol::table scanCode_t = input["KeyCode"].get_or_create<sol::table>();
        sol::table keyMod_t = input["KeyMod"].get_or_create<sol::table>();
        
        //SDL_Keycode
        
        //SDL_Keymod
        keyMod_t["NONE"]       = KMOD_NONE;
        keyMod_t["LSHIFT"]     = KMOD_LSHIFT;
        keyMod_t["RSHIFT"]     = KMOD_RSHIFT;
        keyMod_t["LCTRL"]      = KMOD_LCTRL;
        keyMod_t["RCTRL"]      = KMOD_RCTRL;
        keyMod_t["LALT"]       = KMOD_LALT;
        keyMod_t["RALT"]       = KMOD_RALT;
        keyMod_t["LGUI"]       = KMOD_LGUI;
        keyMod_t["RGUI"]       = KMOD_RGUI;
        keyMod_t["NUM"]        = KMOD_NUM;
        keyMod_t["CAPS"]       = KMOD_CAPS;
        keyMod_t["MODE"]       = KMOD_MODE;
        keyMod_t["RESERVED"]   = KMOD_RESERVED;
        keyMod_t["CTRL"]       = KMOD_CTRL;
        keyMod_t["SHIFT"]      = KMOD_SHIFT;
        keyMod_t["ALT"]        = KMOD_ALT;
        keyMod_t["GUI"]        = KMOD_GUI;
        
        //Functions
        input["is_key_down"] = [](const SDL_Scancode& key) -> bool
        {
            return BFInput::isKeyDown(key);
        };

        input["is_key_up"] = [](const SDL_Scancode& key) -> bool
        {
            return BFInput::isKeyUp(key);
        };

        input["is_key_pressed"] = [](const SDL_Scancode& key) -> bool
        {
            return BFInput::isKeyPressed(key);
        };
        
        input["is_key_down_with_mod"] = [](const SDL_Scancode& key, const SDL_Keymod& mod) -> bool
        {
            return BFInput::isKeyDown(key, mod);
        };

        input["is_key_up_with_mod"] = [](const SDL_Scancode& key, const SDL_Keymod& mod) -> bool
        {
            return BFInput::isKeyUp(key, mod);
        };
    }
}