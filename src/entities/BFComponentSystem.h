#ifndef BLACKFOX_COMPONENTSYSTEM_H
#define BLACKFOX_COMPONENTSYSTEM_H

#include <memory>
#include <cpp-sdl2/event.hpp>
#include <cinject/cinject.h>

#include "BFNonCopyable.h"

namespace BlackFox
{
	class BFApplication;
	class BFWorld;

	/*!
	 * \class	BFComponentSystem
	 *
	 * \brief	BlackFox Component System.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	26/11/2019
	 */
	class BFComponentSystem : private BFNonCopyable
	{
		friend class BFWorld;

	public:

		/*!
		 * \typedef	std::shared_ptr<BFComponentSystem> Ptr
		 *
		 * \brief	Alias for BlackFox component system pointer.
		 */
		typedef std::shared_ptr<BFComponentSystem> Ptr;

		/*!
		 * \fn	BFComponentSystem::BFComponentSystem(std::shared_ptr<BFApplication> application);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	application	The application.
		 */
		CINJECT(BFComponentSystem(std::shared_ptr<BFApplication> application));

		/*!
		 * \fn	virtual BFComponentSystem::~BFComponentSystem() noexcept = default;
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 */
		virtual ~BFComponentSystem() noexcept = default;

		/*!
		 * \fn	virtual void BFComponentSystem::onEvent(const sdl::Event& ev) = 0;
		 *
		 * \brief	React to the given event.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	ev	The event.
		 */
		virtual void onEvent(const sdl::Event& ev) = 0;

		/*!
		 * \fn	virtual void BFComponentSystem::update(float dt) = 0;
		 *
		 * \brief	Updates the system.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	dt	The delta time
		 */
		virtual void update(float dt) = 0;

	private:

		/*!
		 * \fn	void BFComponentSystem::setWorld(BFWorld* world);
		 *
		 * \brief	Sets the world owning the system.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	world	The world.
		 */
		void setWorld(BFWorld* world);

	protected:
		/*! \brief	The application */
		std::shared_ptr<BFApplication> m_application;
		/*! \brief	The world owning the system */
		BFWorld* m_world;
	};
}

#endif