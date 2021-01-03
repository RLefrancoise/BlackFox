#include "BFDataManager.h"

#include <utility>

namespace BlackFox::Editor
{
    struct TextureLoader : entt::resource_loader<TextureLoader, sf::Texture>
    {
        std::shared_ptr<sf::Texture> load(const BFString& path, sf::IntRect rect) const
        {
            auto tex = std::make_shared<sf::Texture>();
            if(!tex->loadFromFile(path))
                BF_EXCEPTION("Failed to load texture {}", path);

            return tex;
        }
    };

	BFDataManager::BFDataManager(BFDataManager&& dataManager) noexcept
	: m_projectData(std::move(dataManager.m_projectData))
	, m_editorData(std::move(dataManager.m_editorData))
	{
	}

	BFDataManager& BFDataManager::operator=(BFDataManager&& dataManager) noexcept
	{
		if(this != &dataManager)
		{
			m_projectData = std::move(dataManager.m_projectData);
			m_editorData = std::move(dataManager.m_editorData);
		}

		return *this;
	}

	bool BFDataManager::hasActiveProject() const
	{
		return m_projectData.get() != nullptr;
	}

	BFProjectData::Ptr BFDataManager::getActiveProject() const
	{
		return m_projectData;
	}

	void BFDataManager::setActiveProject(BFProjectData::Ptr projectData)
	{
		m_projectData = std::move(projectData);
		BF_PRINT(*m_projectData);
		publish<BFProjectChangedEvent>(m_projectData);
	}

	void BFDataManager::closeActiveProject()
	{
		const std::shared_ptr<BFProjectData> emptyData;
		m_projectData = emptyData;
		BF_PRINT("Closed project");
		publish<BFProjectClosedEvent>();
	}

	bool BFDataManager::hasEditorData() const
	{
		return m_editorData.get() != nullptr;
	}

	BFEditorData::Ptr BFDataManager::getEditorData() const
	{
		return m_editorData;
	}

	void BFDataManager::setEditorData(BFEditorData::Ptr editorData)
	{
		m_editorData.swap(editorData);
		BF_PRINT(*m_editorData);
	}

    TextureHandle BFDataManager::getTextureResource(const entt::hashed_string &textureId, const sf::IntRect &rect)
    {
        if(m_textures.contains(textureId))
        {
            return m_textures.handle(textureId);
        }

        return m_textures.load<TextureLoader>(textureId, (m_editorData->config.resourcesPath / std::filesystem::path(textureId.data())).string(), rect);
    }
}
