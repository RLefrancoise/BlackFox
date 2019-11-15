#ifndef BLACKFOX_COMMANDMANAGER_H
#define BLACKFOX_COMMANDMANAGER_H

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>

#include "BFNonCopyable.h"
#include "BFCommand.h" //to use typeid, bfcommand must not be an incomplete type, then no forward declare possible

namespace BlackFox
{
	class BFCommandManager : private BFNonCopyable
	{
	public:

		BFCommandManager();
		BFCommandManager(BFCommandManager&& manager) noexcept;
		~BFCommandManager();

		template <typename C>
		std::shared_ptr<C> createCommand()
		{
			if (!isCommandRegistered<C>())
			{
				registerCommand<C>();
			}

			BFCommand* command = getRegisteredCommand<C>();
			if (command == nullptr) throw std::runtime_error("BFCommandManager:createCommand - command is not registered");

			std::shared_ptr<C> commandPtr(static_cast<C*>(command->clone()));
			return commandPtr;
		}

	private:

		typedef std::unordered_map<std::type_index, BFCommand*> CommandsMap;
		typedef std::unordered_map<std::type_index, BFCommand*>::iterator CommandsMapIterator;

		template <typename C>
		bool isCommandRegistered()
		{
			auto it = m_commands.cbegin();
			for (; it != m_commands.cend(); ++it)
			{
				if (it->first.hash_code() == typeid(C).hash_code()) return true;
			}

			return false;
		}

		template <typename C>
		bool isCommandRegistered(CommandsMapIterator* pos)
		{
			auto it = m_commands.cbegin();
			for (; it != m_commands.cend(); ++it)
			{
				if (it->first.hash_code() == typeid(C).hash_code())
				{
					*pos = it;
					return true;
				}
			}

			pos = nullptr;
			return false;
		}

		template <typename C>
		BFCommand* getRegisteredCommand()
		{
			if (!isCommandRegistered<C>()) return nullptr;
			return m_commands[typeid(C)];
		}

		template <typename C>
		void registerCommand()
		{
			//if command is already registered, don't register again
			if (isCommandRegistered<C>())
			{
				std::cout << "Command " << typeid(C).raw_name() << " already registered" << std::endl;
				return;
			}

			m_commands[typeid(C)] = static_cast<BFCommand*>(new C());
			std::cout << "BFCommandManager::registerCommand - " << typeid(C).raw_name() << " registered" << std::endl;
		}

		template <typename C>
		void unregisterCommand()
		{
			CommandsMapIterator pos;

			if (!isCommandRegistered<C>(&pos))
			{
				std::cout << "Command " << typeid(C).raw_name() << " is not registered" << std::endl;
				return;
			}

			//Delete command
			if (pos->second != nullptr) delete pos->second;
			m_commands.erase(pos);

			std::cout << "BFCommandManager::unregisterCommand - " << typeid(C).raw_name() << " unregistered" << std::endl;
		}

		CommandsMap m_commands;
	};
}

#endif