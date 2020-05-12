#pragma once

#include "BFWindow.h"
#include <TextEditor.h>
#include <filesystem>
#include <unordered_map>

namespace BlackFox::Editor
{	
	class BFTextEditorWindow : public BFWindow<BFTextEditorWindow>
	{
	public:
		explicit BFTextEditorWindow(const std::string& title)
		: BFWindow<BFTextEditorWindow>(title, BFWindowData{ ImGuiWindowFlags_MenuBar, false, true })
		, m_showWhiteSpaces(false)
		{
			initLanguageDefinitions();
			m_textEditor.SetShowWhitespaces(m_showWhiteSpaces);
		}
		
		BFTextEditorWindow* clone() const override = 0;

		virtual void setFile(const std::filesystem::path& filePath);

	protected:
		bool drawContent(float delta) override;
		
		TextEditor m_textEditor;

		bool m_showWhiteSpaces;

		static void initLanguageDefinitions();
		static std::unordered_map<std::string, TextEditor::LanguageDefinition> m_languageDefinitions;
	};
}