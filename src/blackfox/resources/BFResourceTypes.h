#pragma once

#include <entt/core/hashed_string.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "BFExport.h"

namespace BlackFox::Resources
{
	//Types
	typedef entt::hashed_string	ResourceType;

	//Data
	constexpr static ResourceType	RESOURCE_DATA = "resourceData"_hs;
	constexpr static ResourceType	EDITOR_DATA = "editorData"_hs;
	constexpr static ResourceType	PROJECT_DATA = "projectData"_hs;
	constexpr static ResourceType	ENGINE_CONFIG = "engine_config"_hs;

	//Scripts
	constexpr static ResourceType	LUA_COMPONENT_SCRIPT = "luaComponent"_hs;
	constexpr static ResourceType	LUA_SYSTEM_SCRIPT = "luaSystem"_hs;

	//Assets
	constexpr static ResourceType	TEXTURE_ASSET = "texture"_hs;
	constexpr static ResourceType	FONT_ASSET = "font"_hs;

	constexpr static ResourceType	UNKNOWN_TYPE = "unknown"_hs;

	//Categories
	typedef entt::hashed_string ResourceCategory;

	constexpr static ResourceCategory	DATA_CATEGORY = "data"_hs;
	constexpr static ResourceCategory	SCRIPT_CATEGORY = "script"_hs;
	constexpr static ResourceCategory	ASSET_CATEGORY = "asset"_hs;
	constexpr static ResourceCategory	UNKNOWN_CATEGORY = "unknown"_hs;

	struct BLACKFOX_EXPORT ResourceCategoryCompare
	{
		bool operator()(const ResourceCategory& lhs, const ResourceCategory& rhs) const;
		std::size_t operator()(const ResourceCategory& c) const;
	};
	
	const static std::unordered_map<ResourceCategory, std::vector<ResourceType>, ResourceCategoryCompare> TYPES_CATEGORIES = 
	{
		{ DATA_CATEGORY, {EDITOR_DATA, PROJECT_DATA, ENGINE_CONFIG} },
		{ SCRIPT_CATEGORY, {LUA_COMPONENT_SCRIPT, LUA_SYSTEM_SCRIPT} },
		{ ASSET_CATEGORY, {TEXTURE_ASSET} }
	};

	static ResourceCategory getResourceTypeCategory(const ResourceType& type);
}