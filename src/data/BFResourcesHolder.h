#pragma once

#include "BFTypeDefs.h"

namespace BlackFox
{
	class BFResourcesHolder final
	{
	public:
		typedef std::shared_ptr<BFResourcesHolder> Ptr;

		constexpr BFResourcesHolder(const BFResourcesHolder& app) = delete;
		constexpr BFResourcesHolder& operator=(const BFResourcesHolder& app) = delete;
		
		constexpr BFResourcesHolder() = default;
		~BFResourcesHolder() = default;

		BFResourcesHolder(BFResourcesHolder&& holder) noexcept;
		BFResourcesHolder& operator=(BFResourcesHolder&& holder) noexcept;
		
		TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect = sf::IntRect());

	private:
		TextureCache m_textureCache{};
	};
}