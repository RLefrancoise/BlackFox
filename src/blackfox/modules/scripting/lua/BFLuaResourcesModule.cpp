#include "BFLuaResourcesModule.h"
#include "BFResourcesHolder.h"
#include <sol/property.hpp>
#include <sol/overload.hpp>

namespace BlackFox::Scripting::Lua
{
    BFLuaResourcesModule::BFLuaResourcesModule(DiContainer container, sol::state *state, sol::table &parentNamespace)
    : BFLuaModule("Resources", std::move(container), state, parentNamespace)
    {}

    void BFLuaResourcesModule::registerModule()
    {
        //Texture handle

        auto textureHandle_t = m_namespace.new_usertype<TextureHandle>("TextureHandle");

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
                [](TextureHandle& handle, const bool smooth) { handle->setSmooth(smooth); });

        //Srgb
        textureHandle_t["srgb"] = sol::property(
                [](TextureHandle& handle) -> bool { return handle->isSrgb(); },
                [](TextureHandle& handle, const bool srgb) { handle->setSrgb(srgb); });

        //Repeated
        textureHandle_t["repeated"] = sol::property(
                [](TextureHandle& handle) -> bool { return handle->isRepeated(); },
                [](TextureHandle& handle, const bool repeated) { handle->setRepeated(repeated); });

        //Get / Load a texture
        m_namespace["texture"] = sol::overload([&](const std::string& path) -> TextureHandle
                                               {
                                                   auto resourcesHolder = m_container->get<IBFResourcesHolder>();
                                                   return resourcesHolder->loadTexture(path);
                                               }, [&](const std::string& path, const sf::IntRect& rect) -> TextureHandle
                                               {
                                                   auto resourcesHolder = m_container->get<IBFResourcesHolder>();
                                                   return resourcesHolder->loadTexture(path, rect);
                                               });


        // Font

        auto fontHandle_t = m_namespace.new_usertype<FontHandle>("FontHandle");

        m_namespace["font"] = [&](const std::string& path) -> FontHandle
        {
            auto resourcesHolder = m_container->get<IBFResourcesHolder>();
            return resourcesHolder->loadFont(path);
        };
    }
}