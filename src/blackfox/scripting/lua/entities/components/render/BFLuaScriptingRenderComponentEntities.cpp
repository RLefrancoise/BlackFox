#include "BFLuaScriptingRenderComponentEntities.h"

#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "BFSpriteComponent.h"
#include "BFCircleShapeComponent.h"

using namespace BlackFox::Components;

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingRenderComponentEntities, "RenderComponents")

namespace BlackFox
{
	void BFLuaScriptingRenderComponentEntities::registerEntity()
	{
		auto componentsNamespace = componentNamespace();

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

		//Shape
		auto shape_t = componentsNamespace.new_usertype<BFShapeComponent>(
				"Shape",
				sol::base_classes,
				sol::bases<IBFComponent>());
		shape_t["color"] = &BFShapeComponent::color;
		shape_t["origin"] = &BFShapeComponent::origin;

		//Circle shape
		auto circle_t = registerType<BFCircleShapeComponent, BFShapeComponent>();
		circle_t["radius"] = &BFCircleShapeComponent::radius;
	}

	std::string BFLuaScriptingRenderComponentEntities::namespaceName() const
	{
		return "Render";
	}
}