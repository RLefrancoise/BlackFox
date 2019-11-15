#ifndef BLACKFOX_COMMANDMANAGER_H
#define BLACKFOX_COMMANDMANAGER_H

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <fmt/format.h>

#include "BFNonCopyable.h"
#include "BFCommand.h" //to use typeid, bfcommand must not be an incomplete type, then no forward declare possible
#include "BFDebug.h"

namespace BlackFox
{
	/*!
	 * \class	BFCommandManager
	 *
	 * \brief	Manager for BlackFox commands.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	15/11/2019
	 */
	class BFCommandManager : private BFNonCopyable
	{
	public:

		/*!
		 * \fn	BFCommandManager::BFCommandManager();
		 *
		 * \brief	Default constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 */
		BFCommandManager();

		/*!
		 * \fn	BFCommandManager::BFCommandManager(BFCommandManager&& manager) noexcept;
		 *
		 * \brief	Move constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \param [in,out]	manager	The manager.
		 */
		BFCommandManager(BFCommandManager&& manager) noexcept;

		/*!
		 * \fn	BFCommandManager::~BFCommandManager();
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 */
		~BFCommandManager();

		/*!
		 * \fn	template <typename C> std::shared_ptr<C> BFCommandManager::createCommand()
		 *
		 * \brief	Creates a command
		 * 			
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \exception	std::runtime_error	Raised when the command could not be created.
		 *
		 * \tparam	C	Type of the command.
		 *
		 * \returns	The created command.
		 */
		template <typename C>
		std::shared_ptr<C> createCommand()
		{
			if (!isCommandRegistered<C>())
			{
				registerCommand<C>();
			}

			BFCommand* command = getRegisteredCommand<C>();
			if (command == nullptr) BF_EXCEPTION("Command {} is not registered", typeid(C).raw_name())

			std::shared_ptr<C> commandPtr(static_cast<C*>(command->clone()));
			return commandPtr;
		}

	private:

		/*!
		 * \typedef	std::unordered_map<std::type_index, BFCommand*> CommandsMap
		 *
		 * \brief	Defines an alias representing the commands map
		 */
		typedef std::unordered_map<std::type_index, BFCommand*> CommandsMap;

		/*!
		 * \typedef	std::unordered_map<std::type_index, BFCommand*>::iterator CommandsMapIterator
		 *
		 * \brief	Defines an alias representing the commands map iterator
		 */
		typedef std::unordered_map<std::type_index, BFCommand*>::iterator CommandsMapIterator;

		/*!
		 * \fn	void BFCommandManager::clearAllCommands();
		 *
		 * \brief	Clears all commands
		 *
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 */
		void clearAllCommands();

		/*!
		 * \fn	template <typename C> bool BFCommandManager::isCommandRegistered()
		 *
		 * \brief	Queries if the command is registered
		 * 			
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \tparam	C	Type of the command.
		 *
		 * \returns	True if the command is registered, false if not.
		 */
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

		/*!
		 * \fn	template <typename C> bool BFCommandManager::isCommandRegistered(CommandsMapIterator* pos)
		 *
		 * \brief	Queries if a command is registered
		 *
		 * 
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 * 			
		 * \tparam	C	Type of the command.
		 * \param [in,out]	pos	If non-null, the position.
		 *
		 * \returns	True if the command is registered, false if not.
		 */
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

		/*!
		 * \fn	template <typename C> BFCommand* BFCommandManager::getRegisteredCommand()
		 *
		 * \brief	Gets registered command
		 * 			
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \tparam	C	Type of the command.
		 *
		 * \returns	Null if it fails, else the registered command.
		 */
		template <typename C>
		BFCommand* getRegisteredCommand()
		{
			if (!isCommandRegistered<C>()) return nullptr;
			return m_commands[typeid(C)];
		}

		/*!
		 * \fn	template <typename C> void BFCommandManager::registerCommand()
		 *
		 * \brief	Registers a command
		 * 			
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \tparam	C	Type of the command
		 */
		template <typename C>
		void registerCommand()
		{
			//if command is already registered, don't register again
			if (isCommandRegistered<C>())
			{
				BF_PRINT("Command {} already registered", typeid(C).raw_name())
				return;
			}

			m_commands[typeid(C)] = static_cast<BFCommand*>(new C());
			BF_PRINT("{} registered", typeid(C).raw_name())
		}

		/*!
		 * \fn	template <typename C> void BFCommandManager::unregisterCommand()
		 *
		 * \brief	Unregisters a command
		 * 			
		 * \author	Renaud Lefrançoise
		 * \date	15/11/2019
		 *
		 * \tparam	C	Type of the command
		 */
		template <typename C>
		void unregisterCommand()
		{
			CommandsMapIterator pos;

			if (!isCommandRegistered<C>(&pos))
			{
				BF_PRINT("Command {} is not registered", typeid(C).raw_name())
				return;
			}

			//Delete command
			if (pos->second != nullptr) delete pos->second;
			m_commands.erase(pos);

			BF_PRINT("{} unregistered", typeid(C).raw_name())
		}

		/*! \brief	The registered commands */
		CommandsMap m_commands;
	};
}

#endif