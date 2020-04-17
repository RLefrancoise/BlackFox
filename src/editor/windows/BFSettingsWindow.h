#pragma once

#include "BFWindow.h"
#include "BFDataManager.h"

namespace BlackFox::Editor
{
	/**
	 * Settings window
	 */
	class BFSettingsWindow final: public BFWindow<BFSettingsWindow>
	{
	public:
		CINJECT(BFSettingsWindow(BFDataManager::Ptr dataManager));
		BFSettingsWindow* clone() const override;
		
	protected:
		bool drawContent(float delta) override;

	private:
		void applyChanges();
		bool showProjectSettings();
		bool showEditorSettings();
		
		BFDataManager::Ptr m_dataManager;
		BFProjectData m_projectData;
		BFEditorData m_editorData;
	};
}
