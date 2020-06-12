#pragma once

#include <utility>
#include <memory>
#include <SFML/System/String.hpp>

#include "BFExport.h"

namespace BlackFox
{
	/*!
	 * \class	IBFCommand
	 *
	 * \brief	BlackFox command class.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	13/11/2019
	 */
	class BLACKFOX_EXPORT IBFCommand
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFCommand> Ptr
		 *
		 * \brief	Alias for BlackFox Command pointer
		 */
		typedef std::shared_ptr<IBFCommand> Ptr;

		IBFCommand(const IBFCommand&) = delete;
		IBFCommand& operator=(const IBFCommand&) = delete;

		explicit IBFCommand(const sf::String& name, const bool isUndoable = true)
		: m_name(name), m_undoable(isUndoable)
		{}

		virtual ~IBFCommand() noexcept = default;
		IBFCommand(IBFCommand&& cmd) noexcept
		: m_name(cmd.m_name)
		, m_undoable(cmd.m_undoable)
		{}

		IBFCommand& operator=(IBFCommand&& cmd) noexcept
		{
			m_name = cmd.m_name;
			m_undoable = cmd.m_undoable;
			return *this;
		}

		/*!
		 * \fn	virtual BFCommand* BFCommand::clone(void) const = 0;
		 *
		 * \brief	Makes a deep copy of this object
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 *
		 * \returns	A copy of this object.
		 */
		[[nodiscard]] virtual IBFCommand* clone() const = 0;

		virtual void undo() = 0;
		virtual void redo() = 0;

		[[nodiscard]] std::string name() const { return m_name; }
		[[nodiscard]] bool isUndoable() const { return m_undoable; }
		
	private:
		sf::String m_name; //Should not use std::string here (C4251 on MSVC) cuz of DLL export
		bool m_undoable;
	};

	template <class T>
	class BFCommandBase: public IBFCommand
	{
	public:
		using Super = BFCommandBase<T>;
		
		explicit BFCommandBase(const sf::String& name, const bool isUndoable = true): IBFCommand(name, isUndoable) {}
		
		template <typename ...Args>
		void execute(Args&& ...args)
		{
			static_cast<T*>(this)->execute(std::forward<Args>(args)...);
		}
	};
}
