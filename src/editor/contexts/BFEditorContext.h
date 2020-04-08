#pragma once

#include "BFBaseContext.h"

namespace BlackFox::Editor
{
	class BFEditorContext final : public BFBaseContext
	{
	public:
		explicit BFEditorContext(DiContainer container);
		void init() override;
	};
}
