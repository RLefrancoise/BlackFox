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
		std::vector<IBFWindow*> windowsToDestroy;

		//Draw windows
		for (const auto& windowEntry : m_windows)
		{
			for (auto* window : windowEntry.second)
			{
				if (!window->draw())
				{
					windowsToDestroy.push_back(window);
				}
			}
		}

		//Destroy windows that asked to be cleared
		for(auto window : windowsToDestroy)
		{
			destroyWindow(window);
		}
	}

	void BFWindowManager::destroyWindow(IBFWindow* window)
	{
		for (auto& windowTypes : m_windows)
		{
			for (auto it = windowTypes.second.begin(); it != windowTypes.second.end(); ++it)
			{
				if (*it == window)
				{
					BF_PRINT("Window {} destroyed", window->title())
					delete* it;
					windowTypes.second.erase(it);
					break;
				}
			}
		}
	}
}
