#pragma once

#include "BFResourcesHolder.h"

namespace BlackFox::Editor
{
    class BFEditorResourcesHolder final : public IBFResourcesHolder
    {
    public:
        constexpr BFEditorResourcesHolder(const BFEditorResourcesHolder& app) = delete;
        constexpr BFEditorResourcesHolder& operator=(const BFEditorResourcesHolder& app) = delete;

        CINJECT(BFEditorResourcesHolder());
        ~BFEditorResourcesHolder() override = default;

        BFEditorResourcesHolder(BFEditorResourcesHolder&& holder) noexcept = default;
        BFEditorResourcesHolder& operator=(BFEditorResourcesHolder&& holder) noexcept = default;

        TextureHandle loadTexture(const std::string& path) override;
        TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect) override;
        TextureHandle loadTexture(const std::filesystem::path& path) override;
        TextureHandle loadTexture(const std::filesystem::path& path, const sf::IntRect& rect) override;
        TextureHandle loadTextureOrThrow(const std::filesystem::path& path) override;
        TextureHandle loadTextureOrThrow(const std::filesystem::path& path, const sf::IntRect& rect) override;

        FontHandle loadFont(const std::string& path) override;
        FontHandle loadFont(const std::filesystem::path& path) override;
        FontHandle loadFontOrThrow(const std::filesystem::path& path) override;
    };
}