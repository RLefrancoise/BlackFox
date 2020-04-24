#include "BFScriptEditorWindow.h"
#include <fstream>

namespace BlackFox::Editor
{
	BFScriptEditorWindow::BFScriptEditorWindow()
	: Super("Script Editor", BFWindowData{ImGuiWindowFlags_MenuBar, false, true})
	, m_showWhiteSpaces(false)
	{
		m_textEditor.SetShowWhitespaces(m_showWhiteSpaces);
	}

	BFScriptEditorWindow* BFScriptEditorWindow::clone() const
	{
		return new BFScriptEditorWindow();
	}

	void BFScriptEditorWindow::setScript(const std::filesystem::path& scriptPath)
	{
		if (!is_regular_file(scriptPath))
			BF_EXCEPTION("scriptPath is not a regular file");
		
		const auto ext = scriptPath.extension();

		if(ext == ".lua")
		{
			m_textEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
		}
		else
		{
			const TextEditor::LanguageDefinition empty;
			m_textEditor.SetLanguageDefinition(empty);
		}

		//Open script file
		std::ifstream ifs(scriptPath.string());
		if (!ifs.good()) BF_EXCEPTION("Failed to open file {}", scriptPath.string());

		//Set script content to text editor
		const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		m_textEditor.SetText(str);
		
		ifs.close();

		//Set title
		title(fmt::format("Script Editor - {}", scriptPath.filename().string()));
	}

	bool BFScriptEditorWindow::drawContent(float delta)
	{
		auto opened = true;
		
		if(ImGui::BeginMenuBar())
		{
			if(ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save")) {}
				if (ImGui::MenuItem("Close")) opened = false;
				
				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("Options"))
			{
				if(ImGui::Checkbox("Show white spaces", &m_showWhiteSpaces))
				{
					m_textEditor.SetShowWhitespaces(m_showWhiteSpaces);
				}
				
				ImGui::EndMenu();
			}
			
			ImGui::EndMenuBar();
		}
		
		m_textEditor.Render("TextEditor");
		
		return opened;
	}
}
