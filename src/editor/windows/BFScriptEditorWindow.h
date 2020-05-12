#pragma once

#include "BFTextEditorWindow.h"

namespace BlackFox::Editor
{
	class BFScriptEditorWindow final : public BFTextEditorWindow
	{
	public:
		BFScriptEditorWindow();
		BFScriptEditorWindow* clone() const override;
	};
}
