#include "BFRenderSpriteSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "entities/spatial/components/BFPositionComponent.h"
#include "entities/spatial/components/BFRotationComponent.h"
#include "entities/spatial/components/BFScaleComponent.h"
#include "entities/render/components/BFSpriteComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSpriteSystem, "BFRenderSpriteSystem")

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	BFRenderSpriteSystem::BFRenderSpriteSystem(BFApplication::Ptr application)
	: BFComponentSystem(std::move(application))
	{
	}

	void BFRenderSpriteSystem::update(float dt)
	{
		auto group = m_world->entityManager()->group<BFPositionComponent, BFSpriteComponent>();
		for(const auto& entity : group)
		{
		    //Position
			const auto& position = group.get<BFPositionComponent>(entity);
			//Rotation is optional, check if entity has rotation
			const auto* rotation = m_world->entityManager()->try_get<BFRotationComponent>(entity);
			//Scale is optional, check if entity has scale
			const auto* scale = m_world->entityManager()->try_get<BFScaleComponent>(entity);
			//Sprite
			const auto& sprite = group.get<BFSpriteComponent>(entity);

			sf::Sprite s;

			//Set sprite image
			s.setTexture(*sprite.image);

			//Set color
			auto color = sprite.color;
			color.a = sprite.alpha;
			s.setColor(color);

			//Set pivot
			s.setOrigin(sprite.pivot);

			//Set sprite rect
			s.setTextureRect(sprite.rect);

			//Set sprite position
			s.setPosition(position.x, position.y);

			//Rotate sprite
			if(scale != nullptr) s.scale(scale->scaleX, scale->scaleY);

			//Scale sprite
			if(rotation != nullptr) s.rotate(rotation->angle);

			m_application->window()->draw(s);
		}
	}
}