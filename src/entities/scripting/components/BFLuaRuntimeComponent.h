#pragma once

#include <sol/sol.hpp>
#include "BFRuntimeComponent.h"

namespace BlackFox::Components
{
	struct BFLuaRuntimeComponent : BFRuntimeComponent<sol::table>
	{
	};
}