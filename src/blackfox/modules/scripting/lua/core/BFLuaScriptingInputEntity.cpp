#include "BFLuaScriptingInputEntity.h"
#include "BFInput.h"
#include <sol/overload.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingInputEntity, "InputEntities")

using namespace BlackFox::Input;

namespace BlackFox
{
    void BFLuaScriptingInputEntity::registerEntity()
    {

        sol::table input_t = m_namespace["Input"].get_or_create<sol::table>();
        sol::table scanCode_t = input_t["KeyCode"].get_or_create<sol::table>();
        sol::table keyMod_t = input_t["KeyMod"].get_or_create<sol::table>();
        
		scanCode_t["A"]			= sf::Keyboard::Key::A;			   ///< The A key
		scanCode_t["B"]			= sf::Keyboard::Key::B;            ///< The B key
		scanCode_t["C"]			= sf::Keyboard::Key::C;            ///< The C key
		scanCode_t["D"]			= sf::Keyboard::Key::D;            ///< The D key
		scanCode_t["E"]			= sf::Keyboard::Key::E;            ///< The E key
		scanCode_t["F"]			= sf::Keyboard::Key::F;            ///< The F key
		scanCode_t["G"]			= sf::Keyboard::Key::G;            ///< The G key
		scanCode_t["H"]			= sf::Keyboard::Key::H;            ///< The H key
		scanCode_t["I"]			= sf::Keyboard::Key::I;            ///< The I key
		scanCode_t["J"]			= sf::Keyboard::Key::J;            ///< The J key
		scanCode_t["K"]			= sf::Keyboard::Key::K;            ///< The K key
		scanCode_t["L"]			= sf::Keyboard::Key::L;            ///< The L key
		scanCode_t["M"]			= sf::Keyboard::Key::M;            ///< The M key
		scanCode_t["N"]			= sf::Keyboard::Key::N;            ///< The N key
		scanCode_t["O"]			= sf::Keyboard::Key::O;            ///< The O key
		scanCode_t["P"]			= sf::Keyboard::Key::P;            ///< The P key
		scanCode_t["Q"]			= sf::Keyboard::Key::Q;            ///< The Q key
		scanCode_t["R"]			= sf::Keyboard::Key::R;            ///< The R key
		scanCode_t["S"]			= sf::Keyboard::Key::S;            ///< The S key
		scanCode_t["T"]			= sf::Keyboard::Key::T;            ///< The T key
		scanCode_t["U"]			= sf::Keyboard::Key::U;            ///< The U key
		scanCode_t["V"]			= sf::Keyboard::Key::V;            ///< The V key
		scanCode_t["W"]			= sf::Keyboard::Key::W;            ///< The W key
		scanCode_t["X"]			= sf::Keyboard::Key::X;            ///< The X key
		scanCode_t["Y"]			= sf::Keyboard::Key::Y;            ///< The Y key
		scanCode_t["Z"]			= sf::Keyboard::Key::Z;            ///< The Z key
		scanCode_t["Num0"]		= sf::Keyboard::Key::Num0;         ///< The 0 key
		scanCode_t["Num1"]		= sf::Keyboard::Key::Num1;         ///< The 1 key
		scanCode_t["Num2"]		= sf::Keyboard::Key::Num2;         ///< The 2 key
		scanCode_t["Num3"]		= sf::Keyboard::Key::Num3;         ///< The 3 key
		scanCode_t["Num4"]		= sf::Keyboard::Key::Num4;         ///< The 4 key
		scanCode_t["Num5"]		= sf::Keyboard::Key::Num5;         ///< The 5 key
		scanCode_t["Num6"]		= sf::Keyboard::Key::Num6;         ///< The 6 key
		scanCode_t["Num7"]		= sf::Keyboard::Key::Num7;         ///< The 7 key
		scanCode_t["Num8"]		= sf::Keyboard::Key::Num8;         ///< The 8 key
		scanCode_t["Num9"]		= sf::Keyboard::Key::Num9;         ///< The 9 key
		scanCode_t["Escape"]	= sf::Keyboard::Key::Escape;       ///< The Escape key
		scanCode_t["LControl"]	= sf::Keyboard::Key::LControl;     ///< The left Control key
		scanCode_t["LShift"]	= sf::Keyboard::Key::LShift;       ///< The left Shift key
		scanCode_t["LAlt"]		= sf::Keyboard::Key::LAlt;         ///< The left Alt key
        scanCode_t["LSystem"]	= sf::Keyboard::Key::LSystem;      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X); ...
		scanCode_t["RControl"]	= sf::Keyboard::Key::RControl;     ///< The right Control key
		scanCode_t["RShift"]	= sf::Keyboard::Key::RShift;       ///< The right Shift key
		scanCode_t["RAlt"]		= sf::Keyboard::Key::RAlt;         ///< The right Alt key
        scanCode_t["RSystem"]	= sf::Keyboard::Key::RSystem;      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X); ...
		scanCode_t["Menu"]		= sf::Keyboard::Key::Menu;         ///< The Menu key
		scanCode_t["LBracket"]	= sf::Keyboard::Key::LBracket;     ///< The [ key
		scanCode_t["RBracket"]	= sf::Keyboard::Key::RBracket;     ///< The ] key
		scanCode_t["Semicolon"]	= sf::Keyboard::Key::Semicolon;    ///< The ; key
        scanCode_t["Comma"]		= sf::Keyboard::Key::Comma;        ///< The ; key
		scanCode_t["Period"]	= sf::Keyboard::Key::Period;       ///< The . key
		scanCode_t["Quote"]		= sf::Keyboard::Key::Quote;        ///< The ' key
		scanCode_t["Slash"]		= sf::Keyboard::Key::Slash;        ///< The / key
		scanCode_t["Backslash"]	= sf::Keyboard::Key::Backslash;    ///< The \ key
		scanCode_t["Tilde"]		= sf::Keyboard::Key::Tilde;        ///< The ~ key
		scanCode_t["Equal"]		= sf::Keyboard::Key::Equal;        ///< The = key
		scanCode_t["Hyphen"]	= sf::Keyboard::Key::Hyphen;       ///< The - key (hyphen)
		scanCode_t["Space"]		= sf::Keyboard::Key::Space;        ///< The Space key
		scanCode_t["Enter"]		= sf::Keyboard::Key::Enter;        ///< The Enter/Return keys
		scanCode_t["Backspace"]	= sf::Keyboard::Key::Backspace;    ///< The Backspace key
		scanCode_t["Tab"]		= sf::Keyboard::Key::Tab;          ///< The Tabulation key
		scanCode_t["PageUp"]	= sf::Keyboard::Key::PageUp;       ///< The Page up key
		scanCode_t["PageDown"]	= sf::Keyboard::Key::PageDown;     ///< The Page down key
		scanCode_t["End"]		= sf::Keyboard::Key::End;          ///< The End key
		scanCode_t["Home"]		= sf::Keyboard::Key::Home;         ///< The Home key
		scanCode_t["Insert"]	= sf::Keyboard::Key::Insert;       ///< The Insert key
		scanCode_t["Delete"]	= sf::Keyboard::Key::Delete;       ///< The Delete key
		scanCode_t["Add"]		= sf::Keyboard::Key::Add;          ///< The + key
        scanCode_t["Subtract"]	= sf::Keyboard::Key::Subtract;     ///< The - key (minus; usually from numpad)
		scanCode_t["Multiply"]	= sf::Keyboard::Key::Multiply;     ///< The * key
		scanCode_t["Divide"]	= sf::Keyboard::Key::Divide;       ///< The / key
		scanCode_t["Left"]		= sf::Keyboard::Key::Left;         ///< Left arrow
		scanCode_t["Right"]		= sf::Keyboard::Key::Right;        ///< Right arrow
		scanCode_t["Up"]		= sf::Keyboard::Key::Up;           ///< Up arrow
		scanCode_t["Down"]		= sf::Keyboard::Key::Down;         ///< Down arrow
		scanCode_t["Numpad0"]	= sf::Keyboard::Key::Numpad0;      ///< The numpad 0 key
		scanCode_t["Numpad1"]	= sf::Keyboard::Key::Numpad1;      ///< The numpad 1 key
		scanCode_t["Numpad2"]	= sf::Keyboard::Key::Numpad2;      ///< The numpad 2 key
		scanCode_t["Numpad3"]	= sf::Keyboard::Key::Numpad3;      ///< The numpad 3 key
		scanCode_t["Numpad4"]	= sf::Keyboard::Key::Numpad4;      ///< The numpad 4 key
		scanCode_t["Numpad5"]	= sf::Keyboard::Key::Numpad5;      ///< The numpad 5 key
		scanCode_t["Numpad6"]	= sf::Keyboard::Key::Numpad6;      ///< The numpad 6 key
		scanCode_t["Numpad7"]	= sf::Keyboard::Key::Numpad7;      ///< The numpad 7 key
		scanCode_t["Numpad8"]	= sf::Keyboard::Key::Numpad8;      ///< The numpad 8 key
		scanCode_t["Numpad9"]	= sf::Keyboard::Key::Numpad9;      ///< The numpad 9 key
		scanCode_t["F1"]		= sf::Keyboard::Key::F1;           ///< The F1 key
		scanCode_t["F2"]		= sf::Keyboard::Key::F2;           ///< The F2 key
		scanCode_t["F3"]		= sf::Keyboard::Key::F3;           ///< The F3 key
		scanCode_t["F4"]		= sf::Keyboard::Key::F4;           ///< The F4 key
		scanCode_t["F5"]		= sf::Keyboard::Key::F5;           ///< The F5 key
		scanCode_t["F6"]		= sf::Keyboard::Key::F6;           ///< The F6 key
		scanCode_t["F7"]		= sf::Keyboard::Key::F7;           ///< The F7 key
		scanCode_t["F8"]		= sf::Keyboard::Key::F8;           ///< The F8 key
		scanCode_t["F9"]		= sf::Keyboard::Key::F9;           ///< The F9 key
		scanCode_t["F10"]		= sf::Keyboard::Key::F10;          ///< The F10 key
		scanCode_t["F11"]		= sf::Keyboard::Key::F11;          ///< The F11 key
		scanCode_t["F12"]		= sf::Keyboard::Key::F12;          ///< The F12 key
		scanCode_t["F13"]		= sf::Keyboard::Key::F13;          ///< The F13 key
		scanCode_t["F14"]		= sf::Keyboard::Key::F14;          ///< The F14 key
		scanCode_t["F15"]		= sf::Keyboard::Key::F15;          ///< The F15 key
        scanCode_t["Pause"]		= sf::Keyboard::Key::Pause;        ///< The Pause key

        keyMod_t["Alt"]         = BFInput::KeyMod::Alt;
        keyMod_t["Control"]     = BFInput::KeyMod::Control;
        keyMod_t["Shift"]       = BFInput::KeyMod::Shift;
        keyMod_t["System"]      = BFInput::KeyMod::System;

        //Functions
        input_t["isKeyDown"] = sol::overload(
			[&](const sf::Keyboard::Key& key) -> bool
        {
            const auto& input = m_container->get<BFInput>();
            return input->isKeyDown(key);
        },
			[&](const sf::Keyboard::Key& key, const BFInput::KeyMod& mod) -> bool
		{
			const auto& input = m_container->get<BFInput>();
			return input->isKeyDown(key, mod);
		});

        input_t["isKeyUp"] = sol::overload(
			[&](const sf::Keyboard::Key& key) -> bool
        {
            const auto& input = m_container->get<BFInput>();
            return input->isKeyUp(key);
        },
			[&](const sf::Keyboard::Key& key, const BFInput::KeyMod& mod) -> bool
		{
			const auto& input = m_container->get<BFInput>();
			return input->isKeyUp(key, mod);
		});

        input_t["isKeyPressed"] = [&](const sf::Keyboard::Key& key) -> bool
        {
            const auto& input = m_container->get<BFInput>();
            return input->isKeyPressed(key);
        };
    }
}