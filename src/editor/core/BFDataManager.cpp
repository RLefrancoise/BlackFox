#include "BFDataManager.h"

namespace BlackFox::Editor
{
	BFDataManager::BFDataManager() = default;
	
	BFDataManager::BFDataManager(BFDataManager&& dataManager) noexcept
		: m_projectData(std::move(dataManager.m_projectData))
	{
	}

	BFDataManager& BFDataManager::operator=(BFDataManager&& dataManager) noexcept
	{
		m_projectData = std::move(dataManager.m_projectData);
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
	}
}
