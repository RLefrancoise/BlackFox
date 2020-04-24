#pragma once

#include <cinject/cinject.h>
#include <entt/signal/emitter.hpp>

#include "data/BFProjectData.h"
#include "data/BFEditorData.h"
#include "BFResourcesHolder.h"

namespace BlackFox::Editor
{
	class BFDataManager final : public entt::emitter<BFDataManager>
	{
	public:

		/// Events
		
		/*!
		 * Project changed event
		 */
		struct BFProjectChangedEvent
		{
			BFProjectData::Ptr project;
		};

		/*!
		 * Project closed event
		 */
		struct BFProjectClosedEvent
		{};

		/// Class

		typedef std::shared_ptr<BFDataManager> Ptr;
		
		CINJECT(BFDataManager(BFResourcesHolder::Ptr resourcesHolder));
		~BFDataManager() = default;

		BFDataManager(const BFDataManager&) = delete;
		BFDataManager& operator=(const BFDataManager&) = delete;

		BFDataManager(BFDataManager&&) noexcept;
		BFDataManager& operator=(BFDataManager&&) noexcept;

		[[nodiscard]] bool hasActiveProject() const;
		[[nodiscard]] BFProjectData::Ptr getActiveProject() const;
		void setActiveProject(BFProjectData::Ptr projectData);
		void closeActiveProject();

		[[nodiscard]] bool hasEditorData() const;
		[[nodiscard]] BFEditorData::Ptr getEditorData() const;
		void setEditorData(BFEditorData::Ptr editorData);

		TextureHandle getTextureResource(const entt::hashed_string& resource) const;
		
	private:
		BFResourcesHolder::Ptr m_resourcesHolder;
		BFProjectData::Ptr m_projectData;
		BFEditorData::Ptr m_editorData;
	};
}
