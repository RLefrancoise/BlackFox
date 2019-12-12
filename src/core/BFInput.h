#ifndef BLACKFOX_INPUT_H
#define BLACKFOX_INPUT_H

#include <cpp-sdl2/event.hpp>
#include <SDL_keyboard.h>
#include <vector>
#include <memory>

namespace BlackFox
{
    class BFApplication;

    class BFInput
    {
        friend class BFApplication;

    public:
        typedef std::shared_ptr<BFInput> Ptr;

        bool isKeyDown(SDL_Scancode key);
        bool isKeyDown(SDL_Scancode key, SDL_Keymod mod);
        bool isKeyUp(SDL_Scancode key);
        bool isKeyUp(SDL_Scancode key, SDL_Keymod mod);
        bool isKeyPressed(SDL_Scancode key);
    private:
        void updateEvents(const std::vector<sdl::Event>& events);

        std::vector<sdl::Event> polledEvents;
        bool downKeys[SDL_NUM_SCANCODES];
    };
}

#endif //BLACKFOX_INPUT_H
