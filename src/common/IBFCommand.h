#pragma once

#include <utility>


#include "BFTypeDefs.h"

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

		explicit IBFCommand(std::string name, const bool isUndoable = true) : m_name(std::move(name)), m_undoable(isUndoable) {}
		virtual ~IBFCommand(void) noexcept = default;
		IBFCommand(IBFCommand&&) noexcept = default;
		IBFCommand& operator=(IBFCommand&&) noexcept = default;

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
		[[nodiscard]] virtual IBFCommand* clone(void) const = 0;

		virtual void undo() = 0;
		virtual void redo() = 0;

		[[nodiscard]] const std::string& name() const { return m_name; }
		[[nodiscard]] bool isUndoable() const { return m_undoable; }
		
	private:
		std::string m_name;
		bool m_undoable;
	};

	template <class T>
	class BFCommandBase: public IBFCommand
	{
	public:
		using Super = BFCommandBase<T>;
		
		explicit BFCommandBase(const std::string& name, const bool isUndoable = true): IBFCommand(name, isUndoable) {}
		
		template <typename ...Args>
		void execute(Args&& ...args)
		{
			static_cast<T*>(this)->execute(std::forward<Args>(args)...);
		}
	};
}
