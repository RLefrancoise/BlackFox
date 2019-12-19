#include "BFLuaScriptingDataEntities.h"
#include "BFResourcesHolder.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingDataEntities, "DataEntities")

namespace BlackFox
{
	void BFLuaScriptingDataEntities::registerEntity()
	{
		auto resourcesNs = m_namespace["Resources"].get_or_create<sol::table>();

		//Texture handle

		auto textureHandle_t = resourcesNs.new_usertype<TextureHandle>("TextureHandle");

		//Width
		textureHandle_t["width"] = [](TextureHandle& handle) -> unsigned int
		{
			return handle->getSize().x;
		};
		
		//Height
		textureHandle_t["height"] = [](TextureHandle& handle) -> unsigned int
		{
			return handle->getSize().y;
		};

		//Smooth
		textureHandle_t["smooth"] = sol::property(
			[](TextureHandle& handle) -> bool { return handle->isSmooth(); }, 
			[](TextureHandle& handle, bool smooth) { handle->setSmooth(smooth); });

		//Srgb
		textureHandle_t["srgb"] = sol::property(
			[](TextureHandle& handle) -> bool { return handle->isSrgb(); }, 
			[](TextureHandle& handle, bool srgb) { handle->setSrgb(srgb); });

		//Repeated
		textureHandle_t["repeated"] = sol::property(
			[](TextureHandle& handle) -> bool { return handle->isRepeated(); }, 
			[](TextureHandle& handle, bool repeated) { handle->setRepeated(repeated); });

		//Get / Load a texture
		resourcesNs["texture"] = sol::overload([&](const std::string& path) -> TextureHandle
		{
			auto resourcesHolder = m_container->get<BFResourcesHolder>();
			return resourcesHolder->loadTexture(path);
		}, [&](const std::string& path, const sf::IntRect& rect) -> TextureHandle
		{
			auto resourcesHolder = m_container->get<BFResourcesHolder>();
			return resourcesHolder->loadTexture(path, rect);
		});
	}
}