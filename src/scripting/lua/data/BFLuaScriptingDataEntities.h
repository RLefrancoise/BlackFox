#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
	class BFLuaScriptingDataEntities : public IBFLuaScriptingEntity
	{
		BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingDataEntities)
	public:
		void registerEntity() override;
	};
}