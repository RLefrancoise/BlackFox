#include "BFScriptEditorWindow.h"
#include <fstream>

namespace BlackFox::Editor
{
	BFScriptEditorWindow::BFScriptEditorWindow()
	: BFTextEditorWindow("Script Editor")
	{
	}

	BFScriptEditorWindow* BFScriptEditorWindow::clone() const
	{
		return new BFScriptEditorWindow();
	}
}
