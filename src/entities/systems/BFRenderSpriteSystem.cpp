#include <utility>

#include "BFRenderSpriteSystem.h"
#include "BFApplication.h"
#include "BFPositionComponent.h"
#include "BFSpriteComponent.h"

using namespace BlackFox::Components;

namespace BlackFox::Systems
{
	BFRenderSpriteSystem::BFRenderSpriteSystem(std::shared_ptr<BFApplication> application)
	: BFComponentSystem(std::move(application))
	{
	}

	void BFRenderSpriteSystem::update(float dt)
	{
		auto view = m_world->entityManager()->view<BFPositionComponent, BFSpriteComponent>();
		for(auto entity : view)
		{
			auto& position = view.get<BFPositionComponent>(entity);
			auto& sprite = view.get<BFSpriteComponent>(entity);

			const auto& image = sprite.image;
			const auto size = sprite.image.size();

			m_application->renderer().render_copy(
				image, //texture to render
				sprite.rect, //rect of the texture
				sdl::Rect( //position & size on screen
					position.x,
					position.y,
					size.x,
					size.y));
		}
	}
}
