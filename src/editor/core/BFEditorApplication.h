#pragma once

#include <cinject/cinject.h>
#include <memory>

#include "BFTypeDefs.h"

namespace BlackFox::Editor
{
	class BFEditorApplication
	{
	public:
		typedef std::shared_ptr<BFEditorApplication> Ptr;

		constexpr BFEditorApplication() = delete;
		constexpr BFEditorApplication(const BFEditorApplication& app) = delete;
		constexpr BFEditorApplication& operator=(const BFEditorApplication& app) = delete;

		CINJECT(BFEditorApplication(DiContainer container));
		
		~BFEditorApplication() noexcept;
		BFEditorApplication(BFEditorApplication&& app) noexcept;
		BFEditorApplication& operator=(BFEditorApplication&& app) noexcept;

		int init(int argc, char** argv);
		[[nodiscard]] int execute() const;
		void quit() const;

	private:
		DiContainer m_container;
		
		class impl;
		std::shared_ptr<impl> pImpl;

		friend class impl;
	};
}
