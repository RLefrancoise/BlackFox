#pragma once

#include <cinject/cinject.h>

#include "data/BFProjectData.h"

namespace BlackFox::Editor
{
	class BFDataManager
	{
	public:
		typedef std::shared_ptr<BFDataManager> Ptr;
		
		CINJECT(BFDataManager());
		~BFDataManager() = default;

		BFDataManager(const BFDataManager&) = delete;
		BFDataManager& operator=(const BFDataManager&) = delete;

		BFDataManager(BFDataManager&&) noexcept;
		BFDataManager& operator=(BFDataManager&&) noexcept;

		[[nodiscard]] bool hasActiveProject() const;
		[[nodiscard]] BFProjectData::Ptr getActiveProject() const;
		
	private:
		BFProjectData::Ptr m_projectData;
	};
}
