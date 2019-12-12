#ifndef BLACKFOX_COMMAND_H
#define BLACKFOX_COMMAND_H

namespace BlackFox
{
	/*!
	 * \class	BFCommand
	 *
	 * \brief	BlackFox command class.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	13/11/2019
	 */
	class BFCommand
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFCommand> Ptr
		 *
		 * \brief	Alias for BlackFox Command pointer
		 */
		typedef std::shared_ptr<BFCommand> Ptr;

		virtual ~BFCommand(void) noexcept = default;

		/*!
		 * \fn	virtual void BFCommand::execute(void) = 0;
		 *
		 * \brief	Executes the command
		 *
		 * \author	Renaud Lefrançoise
		 * \date	13/11/2019
		 */
		virtual void execute(void) = 0;

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
		virtual BFCommand* clone(void) const = 0;
	};
}

#endif
