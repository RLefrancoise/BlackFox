#pragma once

#include "BFRuntimeComponent.h"
#include "BFLuaScript.h"

namespace BlackFox::Components
{
	struct BFLuaRuntimeComponent : BFRuntimeComponent<BFLuaScript::Ptr>
	{
	};
}