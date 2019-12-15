#include "BFInput.h"
#include "BFUtils.h"

namespace BlackFox
{
    bool BFInput::isKeyDown(const sf::Keyboard::Key key)
    {
        bool keyDown = false;
        for(const auto& ev : m_polledEvents)
        {
            if(ev.type != sf::Event::KeyPressed) continue;
            if(ev.key.code == key)
            {
                keyDown = true;
                break;
            }
        }

        return keyDown;
    }

    bool BFInput::isKeyDown(const sf::Keyboard::Key key, const KeyMod mod)
    {
        bool keyDown = false;
        for(const auto& ev : m_polledEvents)
        {
            if(ev.type != sf::Event::KeyPressed) continue;
            if(ev.key.code == key && hasMod(ev.key, mod))
            {
                keyDown = true;
                break;
            }
        }

        return keyDown;
    }

    bool BFInput::isKeyUp(const sf::Keyboard::Key key)
    {
        bool keyUp = false;
        for(const auto& ev : m_polledEvents)
        {
            if(ev.type != sf::Event::KeyReleased) continue;
            if(ev.key.code == key)
            {
                keyUp = true;
                break;
            }
        }

        return keyUp;
    }

    bool BFInput::isKeyUp(const sf::Keyboard::Key key, const KeyMod mod)
    {
        bool keyUp = false;
        for(const auto& ev : m_polledEvents)
        {
            if(ev.type != sf::Event::KeyReleased) continue;
            if(ev.key.code == key && hasMod(ev.key, mod))
            {
                keyUp = true;
                break;
            }
        }

        return keyUp;
    }

    bool BFInput::isKeyPressed(const sf::Keyboard::Key key)
    {
        return m_downKeys[key];
    }

    void BFInput::updateEvents(const std::vector<sf::Event> &events)
    {
        m_polledEvents = events;
        for(const auto& ev : m_polledEvents)
        {
            if (ev.type != sf::Event::KeyPressed && ev.type != sf::Event::KeyReleased) continue;
            if (ev.key.code == sf::Keyboard::Key::Unknown) continue; //Unknown is -1 so we need to filter it to avoid negative index

            m_downKeys[ev.key.code] = ev.type == sf::Event::KeyPressed;
        }
    }

    bool BFInput::hasMod(const sf::Event::KeyEvent& ev, const KeyMod mod)
    {
	    const auto testAlt = hasFlag(mod, KeyMod::Alt);
	    const auto testControl = hasFlag(mod, KeyMod::Control);
	    const auto testShift = hasFlag(mod, KeyMod::Shift);
	    const auto testSystem = hasFlag(mod, KeyMod::System);

        if (testAlt && !ev.alt) return false;
        if (testControl && !ev.control) return false;
        if (testShift && !ev.shift) return false;
        if (testSystem && !ev.system) return false;

        return true;
    }
}