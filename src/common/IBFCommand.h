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

		virtual ~IBFCommand(void) noexcept = default;
		
		/*!
		 * \fn	virtual void BFCommand::execute(void) = 0;
		 *
		 * \brief	Executes the command
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		//virtual void execute(void) = 0;

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
