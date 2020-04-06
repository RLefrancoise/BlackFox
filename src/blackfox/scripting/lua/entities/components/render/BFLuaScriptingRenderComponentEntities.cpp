#include "BFLuaScriptingRenderComponentEntities.h"

#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "BFSpriteComponent.h"

using namespace BlackFox::Components;

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingRenderComponentEntities, "RenderComponents")

namespace BlackFox
{
	void BFLuaScriptingRenderComponentEntities::registerEntity()
	{
		//Renderable
		registerType<BFRenderableComponent>();
		
		//Depth
		auto depth_t = registerType<BFDepthComponent>();
		depth_t["depth"] = &BFDepthComponent::depth;

		//Sprite
		auto sprite_t = registerType<BFSpriteComponent>();
		sprite_t["image"] = &BFSpriteComponent::image;
		sprite_t["rect"] = &BFSpriteComponent::rect;
		sprite_t["pivot"] = &BFSpriteComponent::pivot;
		sprite_t["color"] = &BFSpriteComponent::color;
	}

	std::string BFLuaScriptingRenderComponentEntities::namespaceName() const
	{
		return "Render";
	}
}