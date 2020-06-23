#include "BFTextureResourceLoader.h"
#include "BFDebug.h"
#include <physfs.hpp>
#include <SFML/System/InputStream.hpp>

namespace BlackFox
{
	/*std::shared_ptr<sf::Texture> BFTextureResourceLoader::load(const std::string& path, const sf::IntRect rect) const
	{
		return load(std::filesystem::path(path), rect);
	}

	std::shared_ptr<sf::Texture> BFTextureResourceLoader::load(const std::filesystem::path& path, const sf::IntRect rect) const
	{
        // Open file from VFS
        PhysFS::ifstream ifs(path.string());

        if(!ifs.good())
        {
            BF_EXCEPTION("Failed to load texture {}. Failed to open file", path.string());
        }

        // Read file bytes and store into memory
        char* buffer = new char[ifs.length()];
        ifs.read(buffer, ifs.length());

        // Load texture
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        const auto loadSuccess = texture->loadFromMemory(buffer, ifs.length(), rect);

        // Delete temp buffer
        delete[] buffer;

        //If failed to load, delete texture and throw
        if(!loadSuccess)
        {
            BF_EXCEPTION("Failed to load texture {}", path.string());
        }

		return texture;
	}*/

    bool BFTextureResourceLoader::loadResource(
        sf::Texture *texture,
        std::unique_ptr<BFVirtualFileInputStream> &&stream,
        sf::IntRect area) const
    {
        return texture->loadFromStream(*stream, area);
    }
}
