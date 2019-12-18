#include "BFLuaScriptingDataEntities.h"
#include "BFResourcesHolder.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingDataEntities, "DataEntities")

namespace BlackFox
{
	void BFLuaScriptingDataEntities::registerEntity()
	{
		auto resourcesNs = m_namespace["Resources"].get_or_create<sol::table>();

		auto textureHandle_t = resourcesNs.new_usertype<TextureHandle>("TextureHandle");
		textureHandle_t["width"] = [](TextureHandle& handle) -> unsigned int
		{
			return handle->getSize().x;
		};

		textureHandle_t["height"] = [](TextureHandle& handle) -> unsigned int
		{
			return handle->getSize().y;
		};

		resourcesNs["getTexture"] = [&](const std::string& path) -> TextureHandle
		{
			auto resourcesHolder = m_container->get<BFResourcesHolder>();
			return resourcesHolder->loadTexture(path);
		};
	}
}