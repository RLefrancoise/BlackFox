#pragma once

#include "BFRuntimeComponent.h"
#include "BFLuaScript.h"

namespace BlackFox::Components
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// BlackFox runtime component for Lua scripting. Component data is a Lua script object.
	/// </summary>
	/// --------------------------------------------------------------------------------
	struct BLACKFOX_EXPORT BFLuaRuntimeComponent final : BFRuntimeComponent<BFLuaScript::Ptr>
	{
	};
}