#pragma once

#include <entt/resource/loader.hpp>
#include <filesystem>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
    struct BLACKFOX_EXPORT BFFontResourceLoader final : entt::loader<BFFontResourceLoader, sf::Font>
    {
        [[nodiscard]] std::shared_ptr<sf::Font> load(const std::string& path) const;
        [[nodiscard]] std::shared_ptr<sf::Font> load(const std::filesystem::path& path) const;
    };
}