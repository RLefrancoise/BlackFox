#pragma once

#include "IBFLuaScriptingEntity.h"

namespace BlackFox
{
	class BLACKFOX_EXPORT BFLuaScriptingDataEntities final : public IBFLuaScriptingEntity
	{
		BF_SCRIPTING_LUA_ENTITY(BFLuaScriptingDataEntities)
	public:
		void registerEntity() override;
	};
}