#ifndef BLACKFOX_INPUT_H
#define BLACKFOX_INPUT_H

#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>

namespace BlackFox
{
    class BFApplication;

    class BFInput
    {
        friend class BFApplication;

    public:

        enum KeyMod : unsigned int
        {
            Alt = 1,
            Control = 2,
            Shift = 4,
            System = 8
        };

        typedef std::shared_ptr<BFInput> Ptr;

        bool isKeyDown(sf::Keyboard::Key key);
        bool isKeyDown(sf::Keyboard::Key key, KeyMod mod);
        bool isKeyUp(sf::Keyboard::Key key);
        bool isKeyUp(sf::Keyboard::Key key, KeyMod mod);
        bool isKeyPressed(sf::Keyboard::Key key);

    private:

        void updateEvents(const std::vector<sf::Event>& events);
        bool hasMod(const sf::Event::KeyEvent& ev, KeyMod mod);

        std::vector<sf::Event> polledEvents;
        bool downKeys[sf::Keyboard::Key::KeyCount];
    };
}

#endif //BLACKFOX_INPUT_H
