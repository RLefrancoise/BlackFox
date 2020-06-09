#ifndef BLACKFOX_COMPONENTSYSTEM_H
#define BLACKFOX_COMPONENTSYSTEM_H

#include <memory>
#include <rttr/rttr_enable.h>

#include "BFTypeDefs.h"

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
	class BLACKFOX_EXPORT BFComponentSystem
	{
		RTTR_ENABLE()

	public:

		/*!
		 * \typedef	std::shared_ptr<BFComponentSystem> Ptr
		 *
		 * \brief	Alias for BlackFox component system pointer.
		 */
		typedef std::shared_ptr<BFComponentSystem> Ptr;

		constexpr BFComponentSystem(const BFComponentSystem& app) = delete;
		constexpr BFComponentSystem& operator=(const BFComponentSystem& app) = delete;
		
        //explicit BFComponentSystem(BFApplication* application);
		BFComponentSystem(BFComponentSystem&& system) noexcept;
		BFComponentSystem& operator=(BFComponentSystem&& system) noexcept;

		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	application	The application.
		 */
		BFComponentSystem(std::shared_ptr<BFApplication> application, std::shared_ptr<BFWorld> world);

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
		//virtual void setWorld(std::shared_ptr<BFWorld> world);

	protected:
		/*! \brief	The application */
		std::shared_ptr<BFApplication> m_application;
		/*! \brief	The world owning the system */
		std::shared_ptr<BFWorld> m_world;
	};
}

#endif