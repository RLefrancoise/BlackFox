#pragma once

#include <entt/core/hashed_string.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace BlackFox::Resources
{
	//Types
	typedef entt::hashed_string	ResourceType;

	//Data
	constexpr static ResourceType	RESOURCE_DATA = "resourceData"_hs;
	constexpr static ResourceType	EDITOR_DATA = "editorData"_hs;
	constexpr static ResourceType	PROJECT_DATA = "projectData"_hs;

	//Scripts
	constexpr static ResourceType	LUA_COMPONENT_SCRIPT = "luaComponent"_hs;
	constexpr static ResourceType	LUA_SYSTEM_SCRIPT = "luaSystem"_hs;
	
	constexpr static ResourceType	UNKNOWN_TYPE = "unknown"_hs;

	//Categories
	typedef entt::hashed_string ResourceCategory;

	constexpr static ResourceCategory	DATA_CATEGORY = "data"_hs;
	constexpr static ResourceCategory	SCRIPT_CATEGORY = "script"_hs;
	constexpr static ResourceCategory	UNKNOWN_CATEGORY = "unknown"_hs;

	struct ResourceCategoryCompare
	{
		bool operator()(const ResourceCategory& lhs, const ResourceCategory& rhs) const;
		std::size_t operator()(const ResourceCategory& c) const;
	};
	
	const static std::unordered_map<ResourceCategory, std::vector<ResourceType>, ResourceCategoryCompare> TYPES_CATEGORIES = 
	{
		{ DATA_CATEGORY, {EDITOR_DATA, PROJECT_DATA} },
		{ SCRIPT_CATEGORY, {LUA_COMPONENT_SCRIPT, LUA_SYSTEM_SCRIPT} }
	};

	static ResourceCategory getResourceTypeCategory(const ResourceType& type);
}