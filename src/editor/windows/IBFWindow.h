#pragma once

namespace BlackFox::Editor
{
	class IBFWindow
	{
	public:
		virtual ~IBFWindow() = default;
		virtual void draw() = 0;
	};
}