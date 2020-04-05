#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
	class BFLuaScriptingSFMLEntities final : public IBFLuaScriptingEntity
	{
		BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingSFMLEntities)

	public:
		void registerEntity() override;
	};
}