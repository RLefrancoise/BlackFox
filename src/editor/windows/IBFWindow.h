#pragma once

#include <memory>
#include <string>

namespace BlackFox::Editor
{
	class IBFWindow
	{
	public:
		typedef std::shared_ptr<IBFWindow> Ptr;
		
		virtual ~IBFWindow() noexcept = default;
		virtual bool draw() = 0;

		[[nodiscard]] virtual IBFWindow* clone() const = 0;

		[[nodiscard]] const char* title() const
		{
			return m_title;
		}

	protected:
		explicit IBFWindow(const char* title)
		{
			m_title = title;
		}

		const char* m_title;
	};
}
