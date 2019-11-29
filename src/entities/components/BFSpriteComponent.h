#ifndef BLACKFOX_SPRITE_COMPONENT_H
#define BLACKFOX_SPRITE_COMPONENT_H

#include <cpp-sdl2/rect.hpp>
#include <cpp-sdl2/texture.hpp>
#include <cpp-sdl2/color.hpp>

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFSpriteComponent //: BFComponent
	{
		sdl::Texture* image;
		sdl::Rect rect;
		sdl::Color color = sdl::Color::White();
		Uint8 alpha = 255;
		SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
	};
}

#endif