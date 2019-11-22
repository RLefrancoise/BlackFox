#ifndef BLACKFOX_ICONTEXT_H
#define BLACKFOX_ICONTEXT_H

#include "IBFInstaller.h"
#include "../BFTypeDefs.h"
#include "../core/BFDebug.h"

namespace BlackFox
{
	/*!
	 * \class	IBFContext
	 *
	 * \brief	Interface for BlackFox DI Context
	 *
	 * \author	Renaud Lefran�oise
	 * \date	22/11/2019
	 */
	class IBFContext
	{
	public:

		/*!
		 * \fn	virtual IBFContext::~IBFContext() noexcept = default;
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefran�oise
		 * \date	22/11/2019
		 */
		virtual ~IBFContext() noexcept = default;

		/*!
		 * \fn	virtual void IBFContext::init() = 0;
		 *
		 * \brief	Initializes the context
		 *
		 * \author	Renaud Lefran�oise
		 * \date	22/11/2019
		 */
		virtual void init() = 0;

		/*!
		 * \fn	virtual void IBFContext::run() = 0;
		 *
		 * \brief	Runs the context
		 *
		 * \author	Renaud Lefran�oise
		 * \date	22/11/2019
		 */
		virtual void run() = 0;

		/*!
		 * \fn	virtual void IBFContext::addInstaller(DiInstaller installer) = 0;
		 *
		 * \brief	Adds an installer to the context
		 *
		 * \author	Renaud Lefran�oise
		 * \date	22/11/2019
		 *
		 * \param	installer	The installer.
		 */
		virtual void addInstaller(DiInstaller installer) = 0;
	};

	/*!
	 * \typedef	std::shared_ptr<IBFContext> DiContext
	 *
	 * \brief	Alias for DI Context pointer
	 */
	typedef std::shared_ptr<IBFContext> DiContext;

	/*!
	 * \fn	template <typename C> static DiContext makeContext(DiContainer container, bool run = true)
	 *
	 * \brief	Makes a DI context
	 *
	 * \tparam	C	Type of the context.
	 * \param	container	The DI container.
	 * \param	run		 	(Optional) True to run the context.
	 *
	 * \returns	The created context.
	 */
	template <typename C>
	static DiContext makeContext(DiContainer container, bool run = true)
	{
		static_assert(std::is_base_of<IBFContext, C>::value, "Type parameter of makeContext must derive from IBFContext");

		auto context = std::make_shared<C>(container);
		container->bind<C>().toConstant(context);

		if(run) context->run();

		return context;
	}
}

#endif