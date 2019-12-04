#ifndef BLACKFOX_INPUT_H
#define BLACKFOX_INPUT_H

#include <cpp-sdl2/event.hpp>
#include <SDL_keyboard.h>
#include <unordered_map>
#include <vector>

namespace BlackFox
{
    class BFInput
    {
    public:
        static bool isKeyDown(SDL_Scancode key, SDL_Keymod mod = KMOD_NONE);
        static bool isKeyUp(SDL_Scancode key, SDL_Keymod mod = KMOD_NONE);
        static bool isKeyPressed(SDL_Scancode key);

        static void updateEvents(const std::vector<sdl::Event>& events);

    private:
        static std::vector<sdl::Event> polledEvents;
        static bool downKeys[SDL_NUM_SCANCODES];
    };
}

#endif //BLACKFOX_INPUT_H
