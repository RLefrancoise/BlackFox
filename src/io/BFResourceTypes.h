#pragma once

#include <entt/core/hashed_string.hpp>
#include <string>
#include <unordered_map>

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
		bool operator()(const ResourceCategory& lhs, const ResourceCategory& rhs) const
		{
			return lhs.value() < rhs.value();
		}

		std::size_t operator()(const ResourceCategory& c) const
		{
			return std::hash<std::string>{}(std::to_string(c.value()));
		}
	};
	
	const static std::unordered_map<ResourceCategory, std::vector<ResourceType>, ResourceCategoryCompare> TYPES_CATEGORIES = 
	{
		{ DATA_CATEGORY, {EDITOR_DATA, PROJECT_DATA} },
		{ SCRIPT_CATEGORY, {LUA_COMPONENT_SCRIPT, LUA_SYSTEM_SCRIPT} }
	};

	static ResourceCategory getResourceTypeCategory(const ResourceType& type)
	{
		for(const auto& entry : TYPES_CATEGORIES)
		{
			if (std::find(entry.second.begin(), entry.second.end(), type) != entry.second.end())
				return entry.first;
		}

		return UNKNOWN_CATEGORY;
	}
}