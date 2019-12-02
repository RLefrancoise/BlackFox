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
		for(const auto& entity : view)
		{
		    //Position
			const auto& position = view.get<BFPositionComponent>(entity);
			//Rotation is optional, check if entity has rotation
			const auto* rotation = m_world->entityManager()->try_get<BFRotationComponent>(entity);
			//Scale is optional, check if entity has scale
			const auto* scale = m_world->entityManager()->try_get<BFScaleComponent>(entity);
			//Sprite
			const auto& sprite = view.get<BFSpriteComponent>(entity);

			const auto* image = sprite.image;
			const auto size = sprite.image->size();

			//Compute sprite scale
			const sdl::Vec2f scaleFactor = { scale != nullptr ? scale->scaleX : 1.0f, scale != nullptr ? scale->scaleY : 1.0f };

			//Compute position according to scale
            const int posX { (int) ((position.x + size.x / 2.0f) - (size.x / 2.0f * scaleFactor.x)) };
            const int posY { (int) ((position.y + size.y / 2.0f) - (size.y / 2.0f * scaleFactor.y)) };

            //Final rect on screen
            const SDL_Rect screenRect { posX, posY, (int) (size.x * scaleFactor.x), (int) (size.y * scaleFactor.y) };

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
            if (rotation != nullptr)
            {
                if(SDL_RenderCopyEx(
                        m_application->renderer().ptr(),
                        image->ptr(),
                        &sprite.rect,
                        &screenRect,
                        rotation->angle.value(),
                        &sprite.center,
                        SDL_FLIP_NONE) < 0)
                {
                    BF_WARNING("Failed to rotate sprite : {}", SDL_GetError())
                }
            }
			else
            {
                m_application->renderer().render_copy(
                    *image, //texture to render
                    sprite.rect, //rect of the texture
                    sdl::Rect(screenRect)); //position & size on screen
			}
		}
	}
}