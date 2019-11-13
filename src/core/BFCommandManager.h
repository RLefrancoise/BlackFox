#ifndef BLACKFOX_COMMANDMANAGER_H
#define BLACKFOX_COMMANDMANAGER_H

#include <rttr/type.h>
#include <vector>
#include <map>

#include "BFNonCopyable.h"

namespace BlackFox
{
	class BFCommand; //forward declare BFCommand

	class BFCommandManager : BFNonCopyable
	{
	public:

		BFCommandManager();
		BFCommandManager(BFCommandManager&& manager) noexcept;
		~BFCommandManager();

		template <class C>
		void addCommand(C* command)
		{
			auto commandType = rttr::type::get<C>();
			//if command is already registered, don't register again
			if (std::find(m_commands.begin(), m_commands.end(), commandType.get_id()) != m_commands.end())
			{
				std::cout << "Command " << commandType.get_name() << " already registered" << std::endl;
				return;
			}

			m_commands.insert(std::make_pair(commandType.get_id(), command));
		}

		template <class C>
		void removeCommand()
		{
			auto commandType = rttr::type::get<C>();
			auto pos = std::find(m_commands.begin(), m_commands.end(), commandType.get_id());
			if (pos == m_commands.end())
			{
				std::cout << "Command " << commandType.get_name() << " is not registered" << std::endl;
				return;
			}

			m_commands.erase(pos);
		}

	private:
		//std::vector<rttr::type> m_commandTypes;
		std::map<int, BFCommand*> m_commands;
	};
}

#endif