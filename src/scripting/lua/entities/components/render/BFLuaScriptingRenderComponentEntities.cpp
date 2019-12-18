#include "BFLuaScriptingRenderComponentEntities.h"

#include "BFSpriteComponent.h"

using namespace BlackFox::Components;

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingRenderComponentEntities, "RenderComponents")

namespace BlackFox
{
	void BFLuaScriptingRenderComponentEntities::registerEntity()
	{
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