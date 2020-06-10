/*********************************************************************
 * \file   BFWindowCommand.h
 * \brief  Base class for Blackfox commands executing for windows
 * 
 * \author Renaud Lefrançoise
 * \date   April 2020
***********************************************************************/
#pragma once

#include "IBFCommand.h"
#include "BFWindow.h"
#include "BFCommandManager.h"

namespace BlackFox::Editor
{
	template<class C, class W>
	class BFWindowCommand : public BFCommandBase<C>
	{
	public:
		/*! \brief Shortcut for subclasses to reference parent type */
		using Super = BFWindowCommand<C, W>;
		
		explicit BFWindowCommand(const std::string& name, BFCommandManager::Ptr commandManager)
		: BFCommandBase<C>(name)
		, m_window { nullptr }
		, m_commandManager { std::move(commandManager) }
		{}

		template<typename ...Args>
		void execute(W* window, Args ...args)
		{
			static_assert(std::is_base_of<IBFWindow, W>::value, "Window type of BFWindowCommand must derive from IBFWindow");
			
			if(m_window != window)
			{
				m_window = window;
				m_window->template on<typename W::BFWindowClosedEvent>([this](const typename W::BFWindowClosedEvent& ev, W& w)
				{
					BF_PRINT("Closed window event for window {}", w.title());
					m_commandManager->removeCommand(this);
				});
			}
		}

	protected:
		W* m_window;
		BFCommandManager::Ptr m_commandManager;
	};
}
