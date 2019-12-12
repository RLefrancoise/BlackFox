#ifndef BLACKFOX_SPRITE_COMPONENT_H
#define BLACKFOX_SPRITE_COMPONENT_H

#include <cpp-sdl2/rect.hpp>
#include <cpp-sdl2/texture.hpp>
#include <cpp-sdl2/color.hpp>

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFSpriteComponent : public IBFComponent
	{
	    BF_COMPONENT("Sprite")

		constexpr BFSpriteComponent()
		{}

	    constexpr BFSpriteComponent(sdl::Texture* img, const sdl::Rect& r, const SDL_Point& ctr, const sdl::Color& c, Uint8 a, SDL_BlendMode bm)
	    : image(img)
	    , rect(r)
	    , center(ctr)
	    , color(c)
	    , alpha(a)
	    , blendMode(bm)
        {}

		sdl::Texture* image = nullptr;
		sdl::Rect rect = sdl::Rect();
		SDL_Point center = SDL_Point{};
		sdl::Color color = sdl::Color::White();
		Uint8 alpha = 255;
		SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
	};
}

#endif