#ifndef BLACKFOX_SPRITE_COMPONENT_H
#define BLACKFOX_SPRITE_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

#include "BFComponent.h"

namespace BlackFox::Components
{
	struct BFSpriteComponent : public IBFComponent
	{
	    BF_COMPONENT("Sprite")

		BFSpriteComponent()
		{}

		BFSpriteComponent(sf::Texture* image, const sf::IntRect& rect, const sf::Vector2f& pivot, const sf::Color& c, unsigned int a)
		: image(image)
		, rect(rect)
		, pivot(pivot)
		, color(c)
		, alpha(a)
		{}

		sf::Texture* image = nullptr;
		sf::IntRect rect;
		sf::Vector2f pivot;
		sf::Color color = sf::Color::White;
		unsigned int alpha = 255;
	};
}

#endif