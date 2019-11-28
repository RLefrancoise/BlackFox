#ifndef BLACKFOX_SPRITE_COMPONENT_H
#define BLACKFOX_SPRITE_COMPONENT_H

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFSpriteComponent : BFComponent
	{
		sdl::Texture image;
		sdl::Rect rect;
	};
}

#endif