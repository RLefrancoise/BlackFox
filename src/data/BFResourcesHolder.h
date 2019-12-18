#pragma once

#include "BFNonCopyable.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	class BFResourcesHolder : private BFNonCopyable
	{
	public:
		typedef std::shared_ptr<BFResourcesHolder> Ptr;

		TextureHandle loadTexture(const std::string& path, const sf::IntRect& rect = sf::IntRect());

	private:
		TextureCache m_textureCache{};
	};
}