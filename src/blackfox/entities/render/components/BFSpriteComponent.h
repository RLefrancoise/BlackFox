#pragma once

#include <utility>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include "BFDrawableComponent.h"
#include "BFTransformableComponent.h"
#include "BFVector2.h"

namespace BlackFox::Components
{
	/*!
	 * Sprite component.
	 */
	struct BLACKFOX_EXPORT BFSpriteComponent final : BFDrawableComponent, BFTransformableComponent
	{
		BF_COMPONENT("Sprite")

		BFSpriteComponent()
		: BFSpriteComponent(TextureHandle{})
		{}

		/*!
		 * Create a new sprite component.
		 * @param image 	Image of the sprite
		 * @param rect 		Image rect to display
		 * @param pivot 	Pivot of the sprite, starting frm top-left
		 * @param c 		Sprite color. Image will be modulated by the color
		 */
		explicit BFSpriteComponent(
				TextureHandle image,
				const sf::IntRect& rect = sf::IntRect(),
				const BFVector2f& pivot = BFVector2f(),
				const sf::Color& c = sf::Color::White)
		: BFDrawableComponent(c)
		, BFTransformableComponent(pivot)
		, image(std::move(image))
		, rect(rect)
		{}

		/*!
		 * Image of the sprite.
		 */
		TextureHandle image;

		/*!
		 * Image rect to display.
		 */
		sf::IntRect rect;
	};
}