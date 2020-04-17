#pragma once

#include <cinject/cinject.h>

#include "data/BFProjectData.h"
#include "data/BFEditorData.h"

namespace BlackFox::Editor
{
	class BFDataManager
	{
	public:
		typedef std::shared_ptr<BFDataManager> Ptr;
		
		CINJECT(BFDataManager()) = default;
		~BFDataManager() = default;

		BFDataManager(const BFDataManager&) = delete;
		BFDataManager& operator=(const BFDataManager&) = delete;

		BFDataManager(BFDataManager&&) noexcept;
		BFDataManager& operator=(BFDataManager&&) noexcept;

		[[nodiscard]] bool hasActiveProject() const;
		[[nodiscard]] BFProjectData::Ptr getActiveProject() const;
		void setActiveProject(BFProjectData::Ptr projectData);

		[[nodiscard]] bool hasEditorData() const;
		[[nodiscard]] BFEditorData::Ptr getEditorData() const;
		void setEditorData(BFEditorData::Ptr editorData);
		
	private:
		BFProjectData::Ptr m_projectData;
		BFEditorData::Ptr m_editorData;
	};
}
