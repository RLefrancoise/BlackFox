#include "BFRenderSystem.h"
#include "BFApplication.h"
#include "BFWorld.h"
#include "BFConfigData.h"
#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "entities/spatial/components/BFTransformComponent.h"
#include "entities/render/components/BFSpriteComponent.h"
#include "BFRigidBodyComponent.h"
#include "BFBoxColliderComponent.h"
#include "BFCircleColliderComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	void drawColliderShape(BFApplication* application, sf::Shape& shape, const BFTransformComponent& transform)
	{
		const auto pixelPosition = application->configData()->gameData.worldToPixels(transform.position.x, transform.position.y);
		shape.setPosition(pixelPosition);

		shape.setRotation(transform.rotation);

		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(application->configData()->debugData.physicsCollidersOutlineColor);
		shape.setOutlineThickness(-application->configData()->debugData.physicsCollidersOutlineThickness);

		application->window()->draw(shape);

		//Draw center
		const float centerRadius = application->configData()->debugData.physicsCollidersCenterRadius;
		sf::CircleShape center(centerRadius);
		center.setFillColor(application->configData()->debugData.physicsCollidersCenterColor);
		center.setOrigin(sf::Vector2f(centerRadius, centerRadius));
		center.setPosition(sf::Vector2f(pixelPosition.x, pixelPosition.y));

		application->window()->draw(center);
	}

	void renderCollider(
		BFApplication::Ptr application,
		BFWorld::Ptr world,
		entt::entity e,
		const BFRigidBodyComponent& rb,
		const BFTransformComponent& transform)
	{
		auto em = world->entityManager();

		sf::Shape* shapePtr = nullptr;

		//Is box collider
		auto* box = em->try_get<BFBoxColliderComponent>(e);
		if (box)
		{
			//Draw collider rectangle
			const auto pixelsSize = application->configData()->gameData.worldToPixels(box->extents.x * 2, box->extents.y * 2);
			sf::RectangleShape shape(pixelsSize);

			const auto pixelsCenter = application->configData()->gameData.worldToPixels(box->center.x, box->center.y);
			const auto origin = sf::Vector2f(pixelsSize.x / 2.f + pixelsCenter.x, pixelsSize.y / 2.f - pixelsCenter.y);
			shape.setOrigin(origin);

			drawColliderShape(application.get(), shape, transform);
		}

		//Is circle collider ?
		auto* circle = em->try_get<BFCircleColliderComponent>(e);
		if(circle)
		{
			//Draw collider circle
			const float pixelsRadius = application->configData()->gameData.worldToPixels(circle->radius);
			sf::CircleShape shape(pixelsRadius);

			const auto origin = sf::Vector2f(pixelsRadius, pixelsRadius);
			shape.setOrigin(origin);

			drawColliderShape(application.get(), shape, transform);
		}
	}

	void renderSprite(
		BFApplication::Ptr application,
		const BFSpriteComponent& sprite,
		const BFTransformComponent& transform)
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

		//Debug colliders
		if (m_application->configData()->debugData.debugPhysics)
		{
			auto debugCollidersView = em->view<const BFRigidBodyComponent, const BFTransformComponent>();
			debugCollidersView.each([&](entt::entity e, const BFRigidBodyComponent& rb, const BFTransformComponent& transform)
			{
				renderCollider(m_application, m_world, e, rb, transform);
			});
		}
	}
}