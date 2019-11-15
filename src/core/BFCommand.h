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
		virtual ~BFCommand(void) {}

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
