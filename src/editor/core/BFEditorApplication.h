#pragma once

#include <cinject/cinject.h>
#include <memory>

#include "BFTypeDefs.h"

namespace BlackFox
{
	class BFCommandManager;
}

namespace BlackFox::Editor
{
	class BFWindowManager;
	class BFDataManager;
	
	class BFEditorApplication
	{
	public:
		typedef std::shared_ptr<BFEditorApplication> Ptr;

		constexpr BFEditorApplication() = delete;
		constexpr BFEditorApplication(const BFEditorApplication& app) = delete;
		constexpr BFEditorApplication& operator=(const BFEditorApplication& app) = delete;

		CINJECT(BFEditorApplication(
			DiContainer container, 
			std::shared_ptr<BFCommandManager> commandManager,
			std::shared_ptr<BFWindowManager> windowManager,
			std::shared_ptr<BFDataManager> dataManager));
		
		~BFEditorApplication() noexcept;
		BFEditorApplication(BFEditorApplication&& app) noexcept;
		BFEditorApplication& operator=(BFEditorApplication&& app) noexcept;

		[[nodiscard]] int execute() const;
		void quit() const;

	private:
		DiContainer m_container;
		
		class impl;
		std::unique_ptr<impl> pImpl;

		friend class impl;
	};
}
