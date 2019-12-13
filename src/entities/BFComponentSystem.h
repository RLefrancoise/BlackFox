#ifndef BLACKFOX_COMPONENTSYSTEM_H
#define BLACKFOX_COMPONENTSYSTEM_H

#include <memory>
#include <cinject/cinject.h>
#include <rttr/rttr_enable.h>

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
	class BFComponentSystem
	{
		RTTR_ENABLE()

	public:

		/*!
		 * \typedef	std::shared_ptr<BFComponentSystem> Ptr
		 *
		 * \brief	Alias for BlackFox component system pointer.
		 */
		typedef std::shared_ptr<BFComponentSystem> Ptr;

        constexpr BFComponentSystem() = delete;

        explicit BFComponentSystem(BFApplication* application);

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
		 * \fn	std::string BFComponentSystem::name() const;
		 *
		 * \brief	Gets the name of the system.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	27/11/2019
		 *
		 * \returns	The name of the system.
		 */
		virtual std::string name() const;

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
		virtual void setWorld(BFWorld* world);

	protected:
		/*! \brief	The application */
		BFApplication* m_application;
		/*! \brief	The world owning the system */
		BFWorld* m_world;
	};
}

#endif