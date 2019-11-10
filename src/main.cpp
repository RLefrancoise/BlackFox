#include <SFML/Window.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    sf::Window window(sf::VideoMode(800, 600), "Black Fox");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

