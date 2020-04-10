#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>

#include "BFTypeDefs.h"
#include "BFDebug.h"
#include "windows/IBFWindow.h"

namespace BlackFox::Editor
{
	class BFWindowManager
	{
	public:
		typedef std::shared_ptr<BFWindowManager> Ptr;
		typedef std::unordered_map<std::type_index, IBFWindow::Ptr> RegisteredWindowsList;
		typedef std::unordered_map <std::type_index, std::vector<IBFWindow*>> WindowsList;

		CINJECT(BFWindowManager(DiContainer container));
		~BFWindowManager() noexcept;

		BFWindowManager(BFWindowManager&& windowManager) noexcept = default;
		BFWindowManager& operator=(BFWindowManager&& windowManager) noexcept = default;

		constexpr BFWindowManager() = delete;
		constexpr BFWindowManager(const BFWindowManager&) = delete;
		constexpr BFWindowManager& operator=(const BFWindowManager&) = delete;

		void update();
		
		template <typename WindowType>
		WindowType* createWindow()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of createWindow must derive from IBFWindow");

			if(!isWindowRegistered<WindowType>())
			{
				registerWindow<WindowType>();
			}
			
			auto window = getRegisteredWindow<WindowType>();
			if (window == nullptr) exception("Window {} is not registered", typeid(WindowType).name());
			
			//Create new window and return it
			auto w = window->clone();
			if (w == nullptr) exception("Failed to clone window {}", typeid(WindowType).name());
			
			m_windows[typeid(WindowType)].push_back(w);
			return static_cast<WindowType*>(m_windows[typeid(WindowType)].back());
		}

		template <typename WindowType>
		void destroyWindow(WindowType* window)
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of destroyWindow must derive from IBFWindow");

			if(!hasWindow<WindowType>()) return;

			auto windows = getWindows<WindowType>();
			for(auto w : windows)
			{
				if (w == window)
				{
					destroyWindow(w);
					//print("Window {} destroyed", typeid(WindowType).name());
					break;
				}
			}
		}

		void destroyWindow(IBFWindow* window);
		
		template <typename WindowType>
		WindowType* getWindow()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of getWindow must derive from IBFWindow");
			
			if (!isWindowRegistered<WindowType>()) exception("Window {} is not registered", typeid(WindowType).name());
			if (!hasWindow<WindowType>()) exception("Window {} not found", typeid(WindowType).name());
			
			return m_windows[typeid(WindowType)].front();
		}

		template <typename WindowType>
		const std::vector<std::shared_ptr<WindowType>>& getWindows()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of getWindows must derive from IBFWindow");

			if (!isWindowRegistered<WindowType>()) exception("Window {} is not registered", typeid(WindowType).name());
			if (!hasWindow<WindowType>()) exception("Window {} not found", typeid(WindowType).name());

			return m_windows[typeid(WindowType)];
		}
		
		template<typename WindowType>
		bool hasWindow()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of hasWindow must derive from IBFWindow");
			
			for (const auto& window : m_windows)
			{
				if (window.first.hash_code() == typeid(WindowType).hash_code()) return true;
			}

			return false;
		}

	private:

		template <typename WindowType>
		[[nodiscard]] bool isWindowRegistered() const
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of isWindowRegistered must derive from IBFWindow");
			
			for (const auto& window : m_registeredWindows)
			{
				if (window.first.hash_code() == typeid(WindowType).hash_code()) return true;
			}

			return false;
		}

		template <typename WindowType>
		void registerWindow()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of registerWindow must derive from IBFWindow");
			
			if (isWindowRegistered<WindowType>())
			{
				print("Window {} already registered", typeid(WindowType).name());
				return;
			}

			m_registeredWindows[typeid(WindowType)] = m_container->get<WindowType>();
			print("Window {} registered", typeid(WindowType).name());
		}

		template <typename WindowType>
		IBFWindow* getRegisteredWindow()
		{
			static_assert(std::is_base_of<IBFWindow, WindowType>::value, "Type parameter of getRegisteredWindow must derive from IBFWindow");
			
			if (!isWindowRegistered<WindowType>()) return nullptr;
			return m_registeredWindows[typeid(WindowType)].get();
		}
		
		DiContainer m_container;
		RegisteredWindowsList m_registeredWindows;
		WindowsList m_windows;
	};
}
