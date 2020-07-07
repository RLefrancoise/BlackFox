#pragma once

#include "BFLuaScriptingComponentEntity.h"

namespace BlackFox
{
	class BLACKFOX_EXPORT BFLuaScriptingPhysicsComponentEntities final : public BFLuaScriptingComponentEntity
	{
		BF_SCRIPTING_LUA_COMPONENT_ENTITY(BFLuaScriptingPhysicsComponentEntities) {}

	public:
		void registerEntity() override;
	protected:
		std::string namespaceName() const override;
	};
}