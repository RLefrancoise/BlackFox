#include "BFRenderSpriteSystem.h"
#include "BFApplication.h"
#include "BFPositionComponent.h"
#include "BFRotationComponent.h"
#include "BFScaleComponent.h"
#include "BFSpriteComponent.h"

BF_SYSTEM_REGISTER(BlackFox::Systems::BFRenderSpriteSystem, "BFRenderSpriteSystem")

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
			//Rotation is optional, check if entity has rotation
			auto* rotation = m_world->entityManager()->try_get<BFRotationComponent>(entity);
			//Scale is optional, check if entity has scale
			auto* scale = m_world->entityManager()->try_get<BFScaleComponent>(entity);
			auto& sprite = view.get<BFSpriteComponent>(entity);

			sdl::Texture* image = sprite.image;
			const auto size = sprite.image->size();

			//Render on screen
			SDL_SetRenderTarget(m_application->renderer().ptr(), nullptr);

			//texture blend mode
			image->set_blendmode(sprite.blendMode);

			//Set texture color
			if(SDL_SetTextureColorMod(sprite.image->ptr(), sprite.color.r, sprite.color.g, sprite.color.b) < 0)
			{
				BF_WARNING("Renderer does not support texture color mod : {}", SDL_GetError())
			}

			//Set texture alpha
			if(SDL_SetTextureAlphaMod(sprite.image->ptr(), sprite.alpha) < 0)
			{
				BF_WARNING("Renderer does not support texture alpha mod : {}", SDL_GetError())
			}

			//Render the sprite
            if(rotation != nullptr /*|| scale != nullptr*/)
            {
                //auto s = scale != nullptr ? sdl::Vec2f(scale->scaleX, scale->scaleY) : sdl::Vec2f(1.0f, 1.0f);

                /*if(rotation != nullptr)
                {*/
                    SDL_Rect screenRect {position.x, position.y, size.x, size.y};
                    if(SDL_RenderCopyEx(
                            m_application->renderer().ptr(),
                            image->ptr(),
                            &sprite.rect,
                            &screenRect,
                            rotation->angle(),
                            &sprite.center,
                            SDL_FLIP_NONE) < 0)
                    {
                        BF_WARNING("Failed to rotate sprite : {}", SDL_GetError())
                    }
                //}
            }
			else
            {
                m_application->renderer().render_copy(
                    *image, //texture to render
                    sprite.rect, //rect of the texture
                    sdl::Rect( //position & size on screen
                            position.x,
                            position.y,
                            size.x,
                            size.y));
			}
		}
	}
}