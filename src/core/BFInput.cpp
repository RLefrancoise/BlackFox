#include "BFInput.h"
#include "BFUtils.h"

namespace BlackFox
{
    bool BFInput::isKeyDown(sf::Keyboard::Key key)
    {
        bool keyDown = false;
        for(const auto& ev : polledEvents)
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

    bool BFInput::isKeyDown(sf::Keyboard::Key key, KeyMod mod)
    {
        bool keyDown = false;
        for(const auto& ev : polledEvents)
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

    bool BFInput::isKeyUp(sf::Keyboard::Key key)
    {
        bool keyUp = false;
        for(const auto& ev : polledEvents)
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

    bool BFInput::isKeyUp(sf::Keyboard::Key key, KeyMod mod)
    {
        bool keyUp = false;
        for(const auto& ev : polledEvents)
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

    bool BFInput::isKeyPressed(sf::Keyboard::Key key)
    {
        return downKeys[key];
    }

    void BFInput::updateEvents(const std::vector<sf::Event> &events)
    {
        polledEvents = events;
        for(const auto& ev : polledEvents)
        {
            if (ev.type != sf::Event::KeyPressed && ev.type != sf::Event::KeyReleased) continue;
            if (ev.key.code == sf::Keyboard::Key::Unknown) continue; //Unknown is -1 so we need to filter it to avoid negative index

            downKeys[ev.key.code] = ev.type == sf::Event::KeyPressed;
        }
    }

    bool BFInput::hasMod(const sf::Event::KeyEvent& ev, KeyMod mod)
    {
        bool testAlt = hasFlag(mod, KeyMod::Alt);
        bool testControl = hasFlag(mod, KeyMod::Control);
        bool testShift = hasFlag(mod, KeyMod::Shift);
        bool testSystem = hasFlag(mod, KeyMod::System);

        if (testAlt && !ev.alt) return false;
        if (testControl && !ev.control) return false;
        if (testShift && !ev.shift) return false;
        if (testSystem && !ev.system) return false;

        return true;
    }
}