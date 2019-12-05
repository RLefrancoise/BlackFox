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
        
        //SDL_Scancode
        scanCode_t["UNKNOWN"] = SDL_SCANCODE_UNKNOWN;
        scanCode_t["A"] = SDL_SCANCODE_A;
        scanCode_t["B"] = SDL_SCANCODE_B;
        scanCode_t["C"] = SDL_SCANCODE_C;
        scanCode_t["D"] = SDL_SCANCODE_D;
        scanCode_t["E"] = SDL_SCANCODE_E;
        scanCode_t["F"] = SDL_SCANCODE_F;
        scanCode_t["G"] = SDL_SCANCODE_G;
        scanCode_t["H"] = SDL_SCANCODE_H;
        scanCode_t["I"] = SDL_SCANCODE_I;
        scanCode_t["J"] = SDL_SCANCODE_J;
        scanCode_t["K"] = SDL_SCANCODE_K;
        scanCode_t["L"] = SDL_SCANCODE_L;
        scanCode_t["M"] = SDL_SCANCODE_M;
        scanCode_t["N"] = SDL_SCANCODE_N;
        scanCode_t["O"] = SDL_SCANCODE_O;
        scanCode_t["P"] = SDL_SCANCODE_P;
        scanCode_t["Q"] = SDL_SCANCODE_Q;
        scanCode_t["R"] = SDL_SCANCODE_R;
        scanCode_t["S"] = SDL_SCANCODE_S;
        scanCode_t["T"] = SDL_SCANCODE_T;
        scanCode_t["U"] = SDL_SCANCODE_U;
        scanCode_t["V"] = SDL_SCANCODE_V;
        scanCode_t["W"] = SDL_SCANCODE_W;
        scanCode_t["X"] = SDL_SCANCODE_X;
        scanCode_t["Y"] = SDL_SCANCODE_Y;
        scanCode_t["Z"] = SDL_SCANCODE_Z;
        scanCode_t["1"] = SDL_SCANCODE_1;
        scanCode_t["2"] = SDL_SCANCODE_2;
        scanCode_t["3"] = SDL_SCANCODE_3;
        scanCode_t["4"] = SDL_SCANCODE_4;
        scanCode_t["5"] = SDL_SCANCODE_5;
        scanCode_t["6"] = SDL_SCANCODE_6;
        scanCode_t["7"] = SDL_SCANCODE_7;
        scanCode_t["8"] = SDL_SCANCODE_8;
        scanCode_t["9"] = SDL_SCANCODE_9;
        scanCode_t["0"] = SDL_SCANCODE_0;
        scanCode_t["RETURN"] = SDL_SCANCODE_RETURN;
        scanCode_t["ESCAPE"] = SDL_SCANCODE_ESCAPE;
        scanCode_t["BACKSPACE"] = SDL_SCANCODE_BACKSPACE;
        scanCode_t["TAB"] = SDL_SCANCODE_TAB;
        scanCode_t["SPACE"] = SDL_SCANCODE_SPACE;
        scanCode_t["MINUS"] = SDL_SCANCODE_MINUS;
        scanCode_t["EQUALS"] = SDL_SCANCODE_EQUALS;
        scanCode_t["LEFTBRACKET"] = SDL_SCANCODE_LEFTBRACKET;
        scanCode_t["RIGHTBRACKET"] = SDL_SCANCODE_RIGHTBRACKET;
        scanCode_t["BACKSLASH"] = SDL_SCANCODE_BACKSLASH;
        scanCode_t["NONUSHASH"] = SDL_SCANCODE_NONUSHASH;
        scanCode_t["SEMICOLON"] = SDL_SCANCODE_SEMICOLON;
        scanCode_t["APOSTROPHE"] = SDL_SCANCODE_APOSTROPHE;
        scanCode_t["GRAVE"] = SDL_SCANCODE_GRAVE;
        scanCode_t["COMMA"] = SDL_SCANCODE_COMMA;
        scanCode_t["PERIOD"] = SDL_SCANCODE_PERIOD;
        scanCode_t["SLASH"] = SDL_SCANCODE_SLASH;
        scanCode_t["CAPSLOCK"] = SDL_SCANCODE_CAPSLOCK;
        scanCode_t["F1"] = SDL_SCANCODE_F1;
        scanCode_t["F2"] = SDL_SCANCODE_F2;
        scanCode_t["F3"] = SDL_SCANCODE_F3;
        scanCode_t["F4"] = SDL_SCANCODE_F4;
        scanCode_t["F5"] = SDL_SCANCODE_F5;
        scanCode_t["F6"] = SDL_SCANCODE_F6;
        scanCode_t["F7"] = SDL_SCANCODE_F7;
        scanCode_t["F8"] = SDL_SCANCODE_F8;
        scanCode_t["F9"] = SDL_SCANCODE_F9;
        scanCode_t["F10"] = SDL_SCANCODE_F10;
        scanCode_t["F11"] = SDL_SCANCODE_F11;
        scanCode_t["F12"] = SDL_SCANCODE_F12;
        scanCode_t["PRINTSCREEN"] = SDL_SCANCODE_PRINTSCREEN;
        scanCode_t["SCROLLLOCK"] = SDL_SCANCODE_SCROLLLOCK;
        scanCode_t["PAUSE"] = SDL_SCANCODE_PAUSE;
        scanCode_t["INSERT"] = SDL_SCANCODE_INSERT;
        scanCode_t["HOME"] = SDL_SCANCODE_HOME;
        scanCode_t["PAGEUP"] = SDL_SCANCODE_PAGEUP;
        scanCode_t["DELETE"] = SDL_SCANCODE_DELETE;
        scanCode_t["END"] = SDL_SCANCODE_END;
        scanCode_t["PAGEDOWN"] = SDL_SCANCODE_PAGEDOWN;
        scanCode_t["RIGHT"] = SDL_SCANCODE_RIGHT;
        scanCode_t["LEFT"] = SDL_SCANCODE_LEFT;
        scanCode_t["DOWN"] = SDL_SCANCODE_DOWN;
        scanCode_t["UP"] = SDL_SCANCODE_UP;
        scanCode_t["NUMLOCKCLEAR"] = SDL_SCANCODE_NUMLOCKCLEAR;
        scanCode_t["KP_DIVIDE"] = SDL_SCANCODE_KP_DIVIDE;
        scanCode_t["KP_MULTIPLY"] = SDL_SCANCODE_KP_MULTIPLY;
        scanCode_t["KP_MINUS"] = SDL_SCANCODE_KP_MINUS;
        scanCode_t["KP_PLUS"] = SDL_SCANCODE_KP_PLUS;
        scanCode_t["KP_ENTER"] = SDL_SCANCODE_KP_ENTER;
        scanCode_t["KP_1"] = SDL_SCANCODE_KP_1;
        scanCode_t["KP_2"] = SDL_SCANCODE_KP_2;
        scanCode_t["KP_3"] = SDL_SCANCODE_KP_3;
        scanCode_t["KP_4"] = SDL_SCANCODE_KP_4;
        scanCode_t["KP_5"] = SDL_SCANCODE_KP_5;
        scanCode_t["KP_6"] = SDL_SCANCODE_KP_6;
        scanCode_t["KP_7"] = SDL_SCANCODE_KP_7;
        scanCode_t["KP_8"] = SDL_SCANCODE_KP_8;
        scanCode_t["KP_9"] = SDL_SCANCODE_KP_9;
        scanCode_t["KP_0"] = SDL_SCANCODE_KP_0;
        scanCode_t["KP_PERIOD"] = SDL_SCANCODE_KP_PERIOD;
        scanCode_t["NONUSBACKSLASH"] = SDL_SCANCODE_NONUSBACKSLASH;
        scanCode_t["APPLICATION"] = SDL_SCANCODE_APPLICATION;
        scanCode_t["POWER"] = SDL_SCANCODE_POWER;
        scanCode_t["KP_EQUALS"] = SDL_SCANCODE_KP_EQUALS;
        scanCode_t["F13"] = SDL_SCANCODE_F13;
        scanCode_t["F14"] = SDL_SCANCODE_F14;
        scanCode_t["F15"] = SDL_SCANCODE_F15;
        scanCode_t["F16"] = SDL_SCANCODE_F16;
        scanCode_t["F17"] = SDL_SCANCODE_F17;
        scanCode_t["F18"] = SDL_SCANCODE_F18;
        scanCode_t["F19"] = SDL_SCANCODE_F19;
        scanCode_t["F20"] = SDL_SCANCODE_F20;
        scanCode_t["F21"] = SDL_SCANCODE_F21;
        scanCode_t["F22"] = SDL_SCANCODE_F22;
        scanCode_t["F23"] = SDL_SCANCODE_F23;
        scanCode_t["F24"] = SDL_SCANCODE_F24;
        scanCode_t["EXECUTE"] = SDL_SCANCODE_EXECUTE;
        scanCode_t["HELP"] = SDL_SCANCODE_HELP;
        scanCode_t["MENU"] = SDL_SCANCODE_MENU;
        scanCode_t["SELECT"] = SDL_SCANCODE_SELECT;
        scanCode_t["STOP"] = SDL_SCANCODE_STOP;
        scanCode_t["AGAIN"] = SDL_SCANCODE_AGAIN;
        scanCode_t["UNDO"] = SDL_SCANCODE_UNDO;
        scanCode_t["CUT"] = SDL_SCANCODE_CUT;
        scanCode_t["COPY"] = SDL_SCANCODE_COPY;
        scanCode_t["PASTE"] = SDL_SCANCODE_PASTE;
        scanCode_t["FIND"] = SDL_SCANCODE_FIND;
        scanCode_t["MUTE"] = SDL_SCANCODE_MUTE;
        scanCode_t["VOLUMEUP"] = SDL_SCANCODE_VOLUMEUP;
        scanCode_t["VOLUMEDOWN"] = SDL_SCANCODE_VOLUMEDOWN;
        scanCode_t["KP_COMMA"] = SDL_SCANCODE_KP_COMMA;
        scanCode_t["KP_EQUALSAS400"] = SDL_SCANCODE_KP_EQUALSAS400;
        scanCode_t["INTERNATIONAL1"] = SDL_SCANCODE_INTERNATIONAL1;
        scanCode_t["INTERNATIONAL2"] = SDL_SCANCODE_INTERNATIONAL2;
        scanCode_t["INTERNATIONAL3"] = SDL_SCANCODE_INTERNATIONAL3;
        scanCode_t["INTERNATIONAL4"] = SDL_SCANCODE_INTERNATIONAL4;
        scanCode_t["INTERNATIONAL5"] = SDL_SCANCODE_INTERNATIONAL5;
        scanCode_t["INTERNATIONAL6"] = SDL_SCANCODE_INTERNATIONAL6;
        scanCode_t["INTERNATIONAL7"] = SDL_SCANCODE_INTERNATIONAL7;
        scanCode_t["INTERNATIONAL8"] = SDL_SCANCODE_INTERNATIONAL8;
        scanCode_t["INTERNATIONAL9"] = SDL_SCANCODE_INTERNATIONAL9;
        scanCode_t["LANG1"] = SDL_SCANCODE_LANG1;
        scanCode_t["LANG2"] = SDL_SCANCODE_LANG2;
        scanCode_t["LANG3"] = SDL_SCANCODE_LANG3;
        scanCode_t["LANG4"] = SDL_SCANCODE_LANG4;
        scanCode_t["LANG5"] = SDL_SCANCODE_LANG5;
        scanCode_t["LANG6"] = SDL_SCANCODE_LANG6;
        scanCode_t["LANG7"] = SDL_SCANCODE_LANG7;
        scanCode_t["LANG8"] = SDL_SCANCODE_LANG8;
        scanCode_t["LANG9"] = SDL_SCANCODE_LANG9; 
        scanCode_t["ALTERASE"] = SDL_SCANCODE_ALTERASE;
        scanCode_t["SYSREQ"] = SDL_SCANCODE_SYSREQ;
        scanCode_t["CANCEL"] = SDL_SCANCODE_CANCEL;
        scanCode_t["CLEAR"] = SDL_SCANCODE_CLEAR;
        scanCode_t["PRIOR"] = SDL_SCANCODE_PRIOR;
        scanCode_t["RETURN2"] = SDL_SCANCODE_RETURN2;
        scanCode_t["SEPARATOR"] = SDL_SCANCODE_SEPARATOR;
        scanCode_t["OUT"] = SDL_SCANCODE_OUT;
        scanCode_t["OPER"] = SDL_SCANCODE_OPER;
        scanCode_t["CLEARAGAIN"] = SDL_SCANCODE_CLEARAGAIN;
        scanCode_t["CRSEL"] = SDL_SCANCODE_CRSEL;
        scanCode_t["EXSEL"] = SDL_SCANCODE_EXSEL;
        scanCode_t["KP_00"] = SDL_SCANCODE_KP_00;
        scanCode_t["KP_000"] = SDL_SCANCODE_KP_000;
        scanCode_t["THOUSANDSSEPARATOR"] = SDL_SCANCODE_THOUSANDSSEPARATOR;
        scanCode_t["DECIMALSEPARATOR"] = SDL_SCANCODE_DECIMALSEPARATOR;
        scanCode_t["CURRENCYUNIT"] = SDL_SCANCODE_CURRENCYUNIT;
        scanCode_t["CURRENCYSUBUNIT"] = SDL_SCANCODE_CURRENCYSUBUNIT;
        scanCode_t["KP_LEFTPAREN"] = SDL_SCANCODE_KP_LEFTPAREN;
        scanCode_t["KP_RIGHTPAREN"] = SDL_SCANCODE_KP_RIGHTPAREN;
        scanCode_t["KP_LEFTBRACE"] = SDL_SCANCODE_KP_LEFTBRACE;
        scanCode_t["KP_RIGHTBRACE"] = SDL_SCANCODE_KP_RIGHTBRACE;
        scanCode_t["KP_TAB"] = SDL_SCANCODE_KP_TAB;
        scanCode_t["KP_BACKSPACE"] = SDL_SCANCODE_KP_BACKSPACE;
        scanCode_t["KP_A"] = SDL_SCANCODE_KP_A;
        scanCode_t["KP_B"] = SDL_SCANCODE_KP_B;
        scanCode_t["KP_C"] = SDL_SCANCODE_KP_C;
        scanCode_t["KP_D"] = SDL_SCANCODE_KP_D;
        scanCode_t["KP_E"] = SDL_SCANCODE_KP_E;
        scanCode_t["KP_F"] = SDL_SCANCODE_KP_F;
        scanCode_t["KP_XOR"] = SDL_SCANCODE_KP_XOR;
        scanCode_t["KP_POWER"] = SDL_SCANCODE_KP_POWER;
        scanCode_t["KP_PERCENT"] = SDL_SCANCODE_KP_PERCENT;
        scanCode_t["KP_LESS"] = SDL_SCANCODE_KP_LESS;
        scanCode_t["KP_GREATER"] = SDL_SCANCODE_KP_GREATER;
        scanCode_t["KP_AMPERSAND"] = SDL_SCANCODE_KP_AMPERSAND;
        scanCode_t["KP_DBLAMPERSAND"] = SDL_SCANCODE_KP_DBLAMPERSAND;
        scanCode_t["KP_VERTICALBAR"] = SDL_SCANCODE_KP_VERTICALBAR;
        scanCode_t["KP_DBLVERTICALBAR"] = SDL_SCANCODE_KP_DBLVERTICALBAR;
        scanCode_t["KP_COLON"] = SDL_SCANCODE_KP_COLON;
        scanCode_t["KP_HASH"] = SDL_SCANCODE_KP_HASH;
        scanCode_t["KP_SPACE"] = SDL_SCANCODE_KP_SPACE;
        scanCode_t["KP_AT"] = SDL_SCANCODE_KP_AT;
        scanCode_t["KP_EXCLAM"] = SDL_SCANCODE_KP_EXCLAM;
        scanCode_t["KP_MEMSTORE"] = SDL_SCANCODE_KP_MEMSTORE;
        scanCode_t["KP_MEMRECALL"] = SDL_SCANCODE_KP_MEMRECALL;
        scanCode_t["KP_MEMCLEAR"] = SDL_SCANCODE_KP_MEMCLEAR;
        scanCode_t["KP_MEMADD"] = SDL_SCANCODE_KP_MEMADD;
        scanCode_t["KP_MEMSUBTRACT"] = SDL_SCANCODE_KP_MEMSUBTRACT;
        scanCode_t["KP_MEMMULTIPLY"] = SDL_SCANCODE_KP_MEMMULTIPLY;
        scanCode_t["KP_MEMDIVIDE"] = SDL_SCANCODE_KP_MEMDIVIDE;
        scanCode_t["KP_PLUSMINUS"] = SDL_SCANCODE_KP_PLUSMINUS;
        scanCode_t["KP_CLEAR"] = SDL_SCANCODE_KP_CLEAR;
        scanCode_t["KP_CLEARENTRY"] = SDL_SCANCODE_KP_CLEARENTRY;
        scanCode_t["KP_BINARY"] = SDL_SCANCODE_KP_BINARY;
        scanCode_t["KP_OCTAL"] = SDL_SCANCODE_KP_OCTAL;
        scanCode_t["KP_DECIMAL"] = SDL_SCANCODE_KP_DECIMAL;
        scanCode_t["KP_HEXADECIMAL"] = SDL_SCANCODE_KP_HEXADECIMAL;
        scanCode_t["LCTRL"] = SDL_SCANCODE_LCTRL;
        scanCode_t["LSHIFT"] = SDL_SCANCODE_LSHIFT;
        scanCode_t["LALT"] = SDL_SCANCODE_LALT;
        scanCode_t["LGUI"] = SDL_SCANCODE_LGUI;
        scanCode_t["RCTRL"] = SDL_SCANCODE_RCTRL;
        scanCode_t["RSHIFT"] = SDL_SCANCODE_RSHIFT;
        scanCode_t["RALT"] = SDL_SCANCODE_RALT;
        scanCode_t["RGUI"] = SDL_SCANCODE_RGUI;
        scanCode_t["MODE"] = SDL_SCANCODE_MODE;
        scanCode_t["AUDIONEXT"] = SDL_SCANCODE_AUDIONEXT;
        scanCode_t["AUDIOPREV"] = SDL_SCANCODE_AUDIOPREV;
        scanCode_t["AUDIOSTOP"] = SDL_SCANCODE_AUDIOSTOP;
        scanCode_t["AUDIOPLAY"] = SDL_SCANCODE_AUDIOPLAY;
        scanCode_t["AUDIOMUTE"] = SDL_SCANCODE_AUDIOMUTE;
        scanCode_t["MEDIASELECT"] = SDL_SCANCODE_MEDIASELECT;
        scanCode_t["WWW"] = SDL_SCANCODE_WWW;
        scanCode_t["MAIL"] = SDL_SCANCODE_MAIL;
        scanCode_t["CALCULATOR"] = SDL_SCANCODE_CALCULATOR;
        scanCode_t["COMPUTER"] = SDL_SCANCODE_COMPUTER;
        scanCode_t["AC_SEARCH"] = SDL_SCANCODE_AC_SEARCH;
        scanCode_t["AC_HOME"] = SDL_SCANCODE_AC_HOME;
        scanCode_t["AC_BACK"] = SDL_SCANCODE_AC_BACK;
        scanCode_t["AC_FORWARD"] = SDL_SCANCODE_AC_FORWARD;
        scanCode_t["AC_STOP"] = SDL_SCANCODE_AC_STOP;
        scanCode_t["AC_REFRESH"] = SDL_SCANCODE_AC_REFRESH;
        scanCode_t["AC_BOOKMARKS"] = SDL_SCANCODE_AC_BOOKMARKS;
        scanCode_t["BRIGHTNESSDOWN"] = SDL_SCANCODE_BRIGHTNESSDOWN;
        scanCode_t["BRIGHTNESSUP"] = SDL_SCANCODE_BRIGHTNESSUP;
        scanCode_t["DISPLAYSWITCH"] = SDL_SCANCODE_DISPLAYSWITCH;
        scanCode_t["KBDILLUMTOGGLE"] = SDL_SCANCODE_KBDILLUMTOGGLE;
        scanCode_t["KBDILLUMDOWN"] = SDL_SCANCODE_KBDILLUMDOWN;
        scanCode_t["KBDILLUMUP"] = SDL_SCANCODE_KBDILLUMUP;
        scanCode_t["EJECT"] = SDL_SCANCODE_EJECT;
        scanCode_t["SLEEP"] = SDL_SCANCODE_SLEEP;
        scanCode_t["APP1"] = SDL_SCANCODE_APP1;
        scanCode_t["APP2"] = SDL_SCANCODE_APP2;
        scanCode_t["AUDIOREWIND"] = SDL_SCANCODE_AUDIOREWIND;
        scanCode_t["AUDIOFASTFORWARD"] = SDL_SCANCODE_AUDIOFASTFORWARD;
        
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