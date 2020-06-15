#include "BFRenderSystem.h"

#include "BFApplication.h"
#include "BFWorld.h"
#include "BFConfigData.h"

#include "BFTransformComponent.h"

#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "BFSpriteComponent.h"
#include "BFCircleShapeComponent.h"
#include "BFBoxShapeComponent.h"

#include "BFRigidBodyComponent.h"
#include "BFBoxColliderComponent.h"
#include "BFCircleColliderComponent.h"

#include <SFML/Graphics.hpp>

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSystem)

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
    /*!
     * Place transformable on screen according to its Transform Component
     *
     * @param application   Application pointer
     * @param transformable Transformable to place
     * @param transform     Transform Component
     *
     * @return              Position on screen in pixels
     */
    BFVector2f placeTransformable(BFApplication* application, sf::Transformable& transformable, const BFTransformComponent& transform)
    {
        const auto pixelPosition = application->configData()->gameData.worldToPixels(transform.position.x, transform.position.y);
        transformable.setPosition(pixelPosition);
        transformable.setRotation(transform.rotation);

        return pixelPosition;
    }

    /*!
     * Render drawable on screen
     *
     * @param application   Application pointer
     * @param drawable      Drawable to render
     */
    void renderDrawable(BFApplication* application, sf::Drawable& drawable)
    {
        application->window()->draw(drawable);
    }

    /*!
     * Place and render element on screen
     *
     * @tparam T            Element type
     * @param application   Application pointer
     * @param element       Element to place and render
     * @param transform     Transform Component
     *
     * @return              Position on screen in pixels
     */
    template<class T>
    BFVector2f placeAndRender(BFApplication* application, T& element, const BFTransformComponent& transform)
    {
        const auto pixelsPosition = placeTransformable(application, element, transform);
        renderDrawable(application, element);

        return pixelsPosition;
    }

	void drawColliderShape(BFApplication* application, sf::Shape& shape, const BFTransformComponent& transform)
	{
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(application->configData()->debugData.physicsCollidersOutlineColor);
		shape.setOutlineThickness(-application->configData()->debugData.physicsCollidersOutlineThickness);

        const auto pixelPosition = placeAndRender(application, shape, transform);

		//Draw center
		const float centerRadius = application->configData()->debugData.physicsCollidersCenterRadius;
		sf::CircleShape center(centerRadius);
		center.setFillColor(application->configData()->debugData.physicsCollidersCenterColor);
		center.setOrigin(sf::Vector2f(centerRadius, centerRadius));
		center.setPosition(sf::Vector2f(pixelPosition.x, pixelPosition.y));

		renderDrawable(application, center);
	}

	void renderCollider(
		BFApplication* application,
		const BFWorld::Ptr& world,
		entt::entity e,
		const BFRigidBodyComponent& rb,
		const BFTransformComponent& transform)
	{
		auto em = world->entityManager();

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

			drawColliderShape(application, shape, transform);
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

			drawColliderShape(application, shape, transform);
		}
	}

	/*!
	 * Render circle shape
	 *
	 * @param application   Application pointer
	 * @param circle        Circle Shape Component
	 * @param transform     Transform Component
	 */
	void renderCircleShape(
        BFApplication* application,
	    const BFCircleShapeComponent& circle,
	    const BFTransformComponent& transform)
    {
	    //Radius
        const float pixelsRadius = application->configData()->gameData.worldToPixels(circle.radius);
        sf::CircleShape shape(pixelsRadius);

	    //Origin
	    const auto pixelsOrigin = application->configData()->gameData.worldToPixels(circle.origin.x, circle.origin.y);
	    shape.setOrigin(pixelsOrigin);

	    //Color
	    shape.setFillColor(circle.color);

	    //Render circle
	    placeAndRender(application, shape, transform);
    }

    /*!
     * Render box shape
     *
     * @param application 	Application pointer
     * @param box 			Box Shape Component
     * @param transform 	Transform Component
     */
    void renderBoxShape(
		BFApplication* application,
		const BFBoxShapeComponent& box,
		const BFTransformComponent& transform)
	{
		//Extents
		const BFVector2f pixelsSize = application->configData()->gameData.worldToPixels(box.extents.x * 2, box.extents.y * 2);
		sf::RectangleShape shape(pixelsSize);

		//Origin
		const auto pixelsOrigin = application->configData()->gameData.worldToPixels(box.origin.x, box.origin.y);
		shape.setOrigin(pixelsOrigin);

		//Color
		shape.setFillColor(box.color);

		//Render box
		placeAndRender(application, shape, transform);
	}

    /*!
     * Render Sprite Component
     *
     * @param application   Application pointer
     * @param sprite        Sprite Component
     * @param transform     Transform Component
     */
	void renderSprite(
		BFApplication* application,
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
		//s.setPosition(application->configData()->gameData.worldToPixels(transform.position.x, transform.position.y));

		//Scale sprite
		const auto pixelsScale = application->configData()->gameData.worldToPixels(transform.scale.x, transform.scale.y);
		s.setScale(pixelsScale.x / sprite.image->getSize().x, pixelsScale.y / sprite.image->getSize().y);

		//Rotate sprite
		//s.setRotation(transform.rotation.value());

		placeAndRender(application, s, transform);
	}
	
	BFRenderSystem::BFRenderSystem(BFApplication::Ptr application, BFWorld::Ptr world)
	: BFComponentSystem(std::move(application), std::move(world))
	{
	}

	void BFRenderSystem::update(float dt)
	{
		auto em = m_world->entityManager();
		auto group = em->group<BFRenderableComponent>(entt::get<BFDepthComponent, const BFTransformComponent>);

		//Sort renderable by depth
		group.sort<BFDepthComponent>([](const BFDepthComponent& lhs, const BFDepthComponent& rhs)
		{
			return lhs.depth > rhs.depth;
		});

		//Render
		group.each([&](entt::entity entity, const BFRenderableComponent& renderable, const BFDepthComponent& depth, const BFTransformComponent& transform)
		{
			//Entity is a sprite
			if(BFSpriteComponent* sprite = em->try_get<BFSpriteComponent>(entity))
			{
				renderSprite(m_application.get(), *sprite, transform);
			}

			//Entity is a circle shape
			if(BFCircleShapeComponent* circle = em->try_get<BFCircleShapeComponent>(entity))
            {
			    renderCircleShape(m_application.get(), *circle, transform);
            }

			//Entity is a box shape
			if(BFBoxShapeComponent* box = em->try_get<BFBoxShapeComponent>(entity))
			{
				renderBoxShape(m_application.get(), *box, transform);
			}
		});

		//Debug colliders
		if (m_application->configData()->debugData.debugPhysics)
		{
			auto debugCollidersView = em->view<const BFRigidBodyComponent, const BFTransformComponent>();
			debugCollidersView.each([&](entt::entity e, const BFRigidBodyComponent& rb, const BFTransformComponent& transform)
			{
				renderCollider(m_application.get(), m_world, e, rb, transform);
			});
		}
	}
}