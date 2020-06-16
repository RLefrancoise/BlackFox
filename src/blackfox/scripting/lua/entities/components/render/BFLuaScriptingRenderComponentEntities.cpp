#include "BFLuaScriptingRenderComponentEntities.h"

#include "BFDepthComponent.h"
#include "BFRenderableComponent.h"
#include "BFSpriteComponent.h"
#include "BFCircleShapeComponent.h"
#include "BFBoxShapeComponent.h"
#include "BFLineComponent.h"

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

		//Drawable
		auto drawable_t = componentsNamespace.new_usertype<BFDrawableComponent>(
				"Drawable",
				sol::base_classes,
				sol::bases<IBFComponent>());
		drawable_t["color"] = &BFDrawableComponent::color;

		//Line
		auto line_t = registerType<BFLineComponent, BFDrawableComponent>();
		line_t["start"] = &BFLineComponent::start;
		line_t["end"] = &BFLineComponent::end;

		//Shape
		auto shape_t = componentsNamespace.new_usertype<BFShapeComponent>(
				"Shape",
				sol::base_classes,
				sol::bases<IBFComponent, BFDrawableComponent>());

		shape_t["origin"] = &BFShapeComponent::origin;

		//Circle shape
		auto circle_t = registerType<BFCircleShapeComponent, BFDrawableComponent, BFShapeComponent>();
		circle_t["radius"] = &BFCircleShapeComponent::radius;

		//Box shape
		auto box_t = registerType<BFBoxShapeComponent, BFDrawableComponent, BFShapeComponent>();
		box_t["extents"] = &BFBoxShapeComponent::extents;
	}

	std::string BFLuaScriptingRenderComponentEntities::namespaceName() const
	{
		return "Render";
	}
}