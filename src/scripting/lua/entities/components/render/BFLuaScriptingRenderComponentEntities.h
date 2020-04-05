#pragma once

#include "BFLuaScriptingComponentEntity.h"

namespace BlackFox
{
	class BFLuaScriptingRenderComponentEntities final : public BFLuaScriptingComponentEntity
	{
		BF_SCRIPTING_LUA_COMPONENT_ENTITY(BFLuaScriptingRenderComponentEntities) {}

	public:
		void registerEntity() override;
	protected:
		std::string namespaceName() const override;
	};
}