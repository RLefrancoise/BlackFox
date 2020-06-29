#include "BFLuaScriptingRenderComponentEntities.h"

#include "BFDepthComponent.h"
#include "BFSpriteComponent.h"
#include "BFCircleShapeComponent.h"
#include "BFBoxShapeComponent.h"
#include "BFLineComponent.h"
#include "BFTextComponent.h"
#include "BFHiddenComponent.h"
#include "BFViewComponent.h"

using namespace BlackFox::Components;

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingRenderComponentEntities, "RenderComponents")

namespace BlackFox
{
	void BFLuaScriptingRenderComponentEntities::registerEntity()
	{
		auto componentsNamespace = componentNamespace();

		//Hidden
		registerType<BFHiddenComponent>();

		//Depth
		auto depth_t = registerType<BFDepthComponent>();
		depth_t["depth"] = &BFDepthComponent::depth;

		//Drawable
		auto drawable_t = componentsNamespace.new_usertype<BFDrawableComponent>("Drawable");
		drawable_t["color"] = &BFDrawableComponent::color;

		//Line
		auto line_t = registerType<BFLineComponent, BFDrawableComponent>();
		line_t["length"] = &BFLineComponent::length;
		line_t["thickness"] = &BFLineComponent::thickness;

		//Transformable
		auto transformable_t = componentsNamespace.new_usertype<BFTransformableComponent>("Transformable");
		transformable_t["origin"] = &BFTransformableComponent::origin;

		//Sprite
		auto sprite_t = registerType<BFSpriteComponent, BFDrawableComponent, BFTransformableComponent>();
		sprite_t["image"] = &BFSpriteComponent::image;
		sprite_t["rect"] = &BFSpriteComponent::rect;
		sprite_t["color"] = &BFSpriteComponent::color;

		//Shape
		auto shape_t = componentsNamespace.new_usertype<BFShapeComponent>(
				"Shape",
				sol::base_classes,
				sol::bases<BFDrawableComponent, BFTransformableComponent>());

		shape_t["origin"] = &BFShapeComponent::origin;
		shape_t["outlineThickness"] = &BFShapeComponent::outlineThickness;
		shape_t["outlineColor"] = &BFShapeComponent::outlineColor;

		//Circle shape
		auto circle_t = registerType<BFCircleShapeComponent, BFDrawableComponent, BFTransformableComponent, BFShapeComponent>();
		circle_t["radius"] = &BFCircleShapeComponent::radius;

		//Box shape
		auto box_t = registerType<BFBoxShapeComponent, BFDrawableComponent, BFTransformableComponent, BFShapeComponent>();
		box_t["extents"] = &BFBoxShapeComponent::extents;

		//Text
		auto text_t = registerType<BFTextComponent, BFDrawableComponent, BFTransformableComponent>();
		text_t["font"] = &BFTextComponent::font;
		text_t["characterSize"] = &BFTextComponent::characterSize;
		text_t["text"] = sol::property(
			[](BFTextComponent& text) -> std::string
			{
				return static_cast<std::string>(text.text);
			},
			[](BFTextComponent& text, const std::string& str)
			{
				text.text = str;
			});
		text_t["outlineThickness"] = &BFTextComponent::outlineThickness;
		text_t["outlineColor"] = &BFTextComponent::outlineColor;

		//View
		auto view_t = registerType<BFViewComponent>();
		view_t["size"] = &BFViewComponent::size;
		view_t["viewport"] = &BFViewComponent::viewport;
	}

	std::string BFLuaScriptingRenderComponentEntities::namespaceName() const
	{
		return "Render";
	}
}