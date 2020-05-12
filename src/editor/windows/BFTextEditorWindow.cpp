#include "BFTextEditorWindow.h"
#include <fstream>

namespace BlackFox::Editor
{
	std::unordered_map<std::string, TextEditor::LanguageDefinition> BFTextEditorWindow::m_languageDefinitions;

	void BFTextEditorWindow::setFile(const std::filesystem::path& filePath)
	{
		if (!is_regular_file(filePath))
			BF_EXCEPTION("filePath is not a regular file");

		const auto ext = filePath.extension();

		//Set language definition
		if(m_languageDefinitions.find(ext.string()) != m_languageDefinitions.end())
		{
			BF_PRINT("Use language definition for extension {}", ext.string());
			m_textEditor.SetLanguageDefinition(m_languageDefinitions[ext.string()]);
		}
		else
		{
			const TextEditor::LanguageDefinition empty;
			m_textEditor.SetLanguageDefinition(empty);
		}

		//Open file
		std::ifstream ifs(filePath);
		if (!ifs.good()) BF_EXCEPTION("Failed to open file {}", filePath.string());

		//Set file content to text editor
		const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		m_textEditor.SetText(str);

		ifs.close();

		//Set title
		title(filePath.filename().string());
	}

	bool BFTextEditorWindow::drawContent(float delta)
	{
		auto opened = true;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save")) {}
				if (ImGui::MenuItem("Close")) opened = false;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", nullptr, false, m_textEditor.CanUndo())) m_textEditor.Undo();
				if (ImGui::MenuItem("Redo", nullptr, false, m_textEditor.CanRedo())) m_textEditor.Redo();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				if (ImGui::Checkbox("Show white spaces", &m_showWhiteSpaces))
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

	void BFTextEditorWindow::initLanguageDefinitions()
	{
		static auto init = false;
		if (init) return;

		//Lua
		m_languageDefinitions.insert(std::make_pair(".lua", TextEditor::LanguageDefinition::Lua()));
		
		//Ini file
		TextEditor::LanguageDefinition ini;
		ini.mName = "Ini";
		
		ini.mCaseSensitive = true;
		ini.mAutoIndentation = false;
		
		ini.mSingleLineComment = ";";
		ini.mCommentStart = ";";

		static const char* const INI_KEYWORDS[] = {"true", "false"};

		for (const auto& k : INI_KEYWORDS)
			ini.mKeywords.insert(k);
		
		ini.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
		ini.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", TextEditor::PaletteIndex::Number));
		ini.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
		ini.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(R"([\[\]\=])", TextEditor::PaletteIndex::Punctuation));

		m_languageDefinitions.insert(std::make_pair(".ini", ini));
	}
}
