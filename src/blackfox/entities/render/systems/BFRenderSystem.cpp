#include "BFRenderSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFConfigData.h"
#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "entities/spatial/components/BFTransformComponent.h"
#include "entities/render/components/BFSpriteComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	void renderSprite(BFApplication::Ptr application, const BFSpriteComponent& sprite, const BFTransformComponent& transform)
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
		s.setPosition(application->configData()->gameData.worldToPixels(transform.position.x, transform.position.y));

		//Scale sprite
		const auto pixelsScale = application->configData()->gameData.worldToPixels(transform.scale.x, transform.scale.y);
		s.setScale(pixelsScale.x / sprite.image->getSize().x, pixelsScale.y / sprite.image->getSize().y);

		//Rotate sprite
		s.setRotation(transform.rotation.value());

		application->window()->draw(s);
	}
	
	BFRenderSystem::BFRenderSystem(BFApplication::Ptr application, BFWorld::Ptr world)
	: BFComponentSystem(std::move(application), std::move(world))
	{
	}

	void BFRenderSystem::update(float dt)
	{
		auto em = m_world->entityManager();
		auto group = em->group<BFRenderableComponent>(entt::get<BFDepthComponent, BFTransformComponent>);

		//Sort renderable by depth
		group.sort<BFDepthComponent>([](const BFDepthComponent& lhs, const BFDepthComponent& rhs)
		{
			return lhs.depth > rhs.depth;
		});

		group.each([&](auto entity, auto& renderable, auto& depth, auto& transform)
		{
			//Entity is a sprite
			if(BFSpriteComponent* sprite = em->try_get<BFSpriteComponent>(entity))
			{
				renderSprite(m_application, *sprite, transform);
			}
		});
	}
}