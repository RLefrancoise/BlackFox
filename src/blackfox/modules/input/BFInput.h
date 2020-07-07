#pragma once

#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox::Input
{
    class BFInputModule;

    class BLACKFOX_EXPORT BFInput
    {
    public:
        friend class BFInputModule;

        enum KeyMod : unsigned int
        {
            Alt = 1,
            Control = 2,
            Shift = 4,
            System = 8
        };

        typedef std::shared_ptr<BFInput> Ptr;

        BFInput();

        bool isKeyDown(sf::Keyboard::Key key);
        bool isKeyDown(sf::Keyboard::Key key, KeyMod mod);
        bool isKeyUp(sf::Keyboard::Key key);
        bool isKeyUp(sf::Keyboard::Key key, KeyMod mod);
        bool isKeyPressed(sf::Keyboard::Key key);

    private:
        void updateEvents(const std::vector<sf::Event>& events);
        static bool hasMod(const sf::Event::KeyEvent& ev, KeyMod mod);

        std::vector<sf::Event> m_polledEvents;
        bool m_downKeys[sf::Keyboard::Key::KeyCount];
    };
}