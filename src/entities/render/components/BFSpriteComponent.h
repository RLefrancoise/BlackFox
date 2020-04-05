#ifndef BLACKFOX_SPRITE_COMPONENT_H
#define BLACKFOX_SPRITE_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include "BFComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
	struct BFSpriteComponent final : IBFComponent
	{
		BF_COMPONENT("Sprite")

		BFSpriteComponent() = default;

		BFSpriteComponent(const TextureHandle& image, const sf::IntRect& rect, const BFVector2f& pivot, const sf::Color& c)
		: image(image)
		, rect(rect)
		, pivot(pivot)
		, color(c)
		{}

		TextureHandle image;
		sf::IntRect rect;
		BFVector2f pivot;
		sf::Color color = sf::Color::White;
	};
}

#endif