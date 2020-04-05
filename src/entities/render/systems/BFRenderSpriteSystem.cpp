#include "BFRenderSpriteSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFConfigData.h"
#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "entities/spatial/components/BFTransformComponent.h"
#include "entities/render/components/BFSpriteComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSpriteSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	BFRenderSpriteSystem::BFRenderSpriteSystem(BFApplication::Ptr application)
	: BFComponentSystem(std::move(application))
	{
	}

	void BFRenderSpriteSystem::update(float dt)
	{
		auto group = m_world->entityManager()->group<BFRenderableComponent, BFSpriteComponent>(entt::get<BFDepthComponent, BFTransformComponent>);

		//Sort sprite by depth
		group.sort<BFDepthComponent>([&group](const BFDepthComponent& lhs, const BFDepthComponent& rhs)
		{
			return lhs.depth > rhs.depth;
		});
		
		//Render
		group.each([&](auto entity, auto& renderable, auto& sprite, auto& depth, auto& transform)
		{
			sf::Sprite s;

			//Set sprite image
			if (sprite.image)
			{
				s.setTexture(sprite.image);
			}

			//Set color
			s.setColor(sprite.color);

			//Set pivot
			s.setOrigin(sprite.pivot);

			//Set sprite rect
			s.setTextureRect(sprite.rect);

			//Set sprite position
			s.setPosition(m_application->configData()->gameData.worldToPixels(transform.position.x, transform.position.y));

			//Scale sprite
			const auto pixelsScale = m_application->configData()->gameData.worldToPixels(transform.scale.x, transform.scale.y);
			s.setScale(pixelsScale.x / sprite.image->getSize().x, pixelsScale.y / sprite.image->getSize().y);

			//Rotate sprite
			s.setRotation(transform.rotation.value());

			m_application->window()->draw(s);
		});
	}
}