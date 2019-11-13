#include "BFCommandManager.h"
#include "BFCommand.h"

#include <iostream>

using namespace rttr;

namespace BlackFox
{
	BFCommandManager::BFCommandManager()
	{
		/*auto command_type = type::get<BFCommand>();
		auto commandTypes = command_type.get_derived_classes();

		for each (type t in commandTypes)
		{
			if (t.is_pointer()) continue;
			if (!t.is_valid()) continue;

			std::cout << "Command " << t.get_name() << " found" << std::endl;
			m_commandTypes.emplace_back(t);
		}*/
	}

	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept
	{
		/*m_commandTypes.clear();

		for each (auto t in manager.m_commandTypes)
		{
			m_commandTypes.emplace_back(t);
		}*/

		/*m_commands.clear();
		for each (auto command in manager.m_commands)
		{
			m_commands.insert(std::make_pair(command.first, command.second));
		}*/
	}

	BFCommandManager::~BFCommandManager()
	{
		for each (auto command in m_commands)
		{
			delete command.second;
			command.second = nullptr;
		}
	}
}