#pragma once

#include "BFWindow.h"
#include <TextEditor.h>
#include <filesystem>

namespace BlackFox::Editor
{
	class BFScriptEditorWindow final : public BFWindow<BFScriptEditorWindow>
	{
	public:
		BFScriptEditorWindow();
		BFScriptEditorWindow* clone() const override;

		void setScript(const std::filesystem::path& scriptPath);

	protected:
		bool drawContent(float delta) override;

	private:
		TextEditor m_textEditor;

		bool m_showWhiteSpaces;
	};
}
