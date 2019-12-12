#include "BFInput.h"

namespace BlackFox
{
    bool BFInput::isKeyDown(SDL_Scancode key)
    {
        bool keyDown = false;
        for(const auto& ev : polledEvents)
        {
            if(ev.type != SDL_KEYDOWN) continue;
            if(ev.key.keysym.scancode == key)
            {
                keyDown = true;
                break;
            }
        }

        return keyDown;
    }

    bool BFInput::isKeyDown(SDL_Scancode key, SDL_Keymod mod)
    {
        bool keyDown = false;
        for(const auto& ev : polledEvents)
        {
            if(ev.type != SDL_KEYDOWN) continue;
            if(ev.key.keysym.scancode == key && ev.key.keysym.mod == mod)
            {
                keyDown = true;
                break;
            }
        }

        return keyDown;
    }

    bool BFInput::isKeyUp(SDL_Scancode key)
    {
        bool keyUp = false;
        for(const auto& ev : polledEvents)
        {
            if(ev.type != SDL_KEYUP) continue;
            if(ev.key.keysym.scancode == key)
            {
                keyUp = true;
                break;
            }
        }

        return keyUp;
    }

    bool BFInput::isKeyUp(SDL_Scancode key, SDL_Keymod mod)
    {
        bool keyUp = false;
        for(const auto& ev : polledEvents)
        {
            if(ev.type != SDL_KEYUP) continue;
            if(ev.key.keysym.scancode == key && ev.key.keysym.mod == mod)
            {
                keyUp = true;
                break;
            }
        }

        return keyUp;
    }

    bool BFInput::isKeyPressed(SDL_Scancode key)
    {
        return downKeys[key];
    }

    void BFInput::updateEvents(const std::vector<sdl::Event> &events)
    {
        polledEvents = events;
        for(const auto& ev : polledEvents)
        {
            if(ev.type != SDL_KEYDOWN && ev.type != SDL_KEYUP) continue;
            downKeys[ev.key.keysym.scancode] = ev.type == SDL_KEYDOWN;
        }
    }
}