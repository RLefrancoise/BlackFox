#pragma once

#include <memory>

namespace BlackFox::Editor
{
	class IBFWindow
	{
	public:
		typedef std::shared_ptr<IBFWindow> Ptr;
		
		virtual ~IBFWindow() noexcept = default;
		virtual void draw() = 0;

		virtual IBFWindow* clone() const = 0;
	};
}