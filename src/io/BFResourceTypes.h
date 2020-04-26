#pragma once

#include <entt/core/hashed_string.hpp>

namespace BlackFox
{
	typedef entt::hashed_string	ResourceType;

	//Data
	constexpr static ResourceType	EDITOR_DATA = "editorData"_hs;
	constexpr static ResourceType	PROJECT_DATA = "projectData"_hs;

	//Scripts
	constexpr static ResourceType	LUA_COMPONENT = "luaComponent"_hs;
	constexpr static ResourceType	LUA_SYSTEM = "luaSystem"_hs;
	
	constexpr static ResourceType	UNKNOWN = "unknown"_hs;
}