#pragma once

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

		IBFCommand() = default;
		virtual ~IBFCommand(void) noexcept = default;
		constexpr IBFCommand(IBFCommand&&) noexcept = default;
		constexpr IBFCommand& operator=(IBFCommand&&) noexcept = default;

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
	};

	template <class T>
	class BFCommandBase: public IBFCommand
	{
	public:
		template <typename ...Args>
		void execute(Args&& ...args)
		{
			static_cast<T*>(this)->execute(std::forward<Args>(args)...);
		}
	};
}
