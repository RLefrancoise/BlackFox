#include "BFWindowManager.h"

namespace BlackFox::Editor
{
	BFWindowManager::BFWindowManager(DiContainer container)
		: m_container(std::move(container))
	{
	}

	BFWindowManager::~BFWindowManager() noexcept
	{
		for (const auto& windowEntry : m_windows)
			for (auto* window : windowEntry.second)
				delete window;
	}

	void BFWindowManager::update()
	{
		for (const auto& windowEntry : m_windows)
			for (auto* window : windowEntry.second)
				window->draw();
	}
}
