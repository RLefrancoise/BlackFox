#include "BFDataManager.h"

#include <utility>

namespace BlackFox::Editor
{
	BFDataManager::BFDataManager(IBFResourcesHolder::Ptr resourcesHolder)
		: m_resourcesHolder(std::move(resourcesHolder))
	{
	}

	BFDataManager::BFDataManager(BFDataManager&& dataManager) noexcept
	: m_resourcesHolder(std::move(dataManager.m_resourcesHolder))
	, m_projectData(std::move(dataManager.m_projectData))
	, m_editorData(std::move(dataManager.m_editorData))
	{
	}

	BFDataManager& BFDataManager::operator=(BFDataManager&& dataManager) noexcept
	{
		m_resourcesHolder = std::move(dataManager.m_resourcesHolder);
		m_projectData = std::move(dataManager.m_projectData);
		m_editorData = std::move(dataManager.m_editorData);
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
		m_editorData = std::move(editorData);
		BF_PRINT(*m_editorData);
	}

	TextureHandle BFDataManager::getTextureResource(const entt::hashed_string& resource) const
	{
		return m_resourcesHolder->loadTexture(m_editorData->config.resourcesPath / resource.data());
	}
}
