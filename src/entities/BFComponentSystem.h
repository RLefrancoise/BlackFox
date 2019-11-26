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

	class BFComponentSystem : private BFNonCopyable
	{
		friend class BFWorld;
	public:

		typedef std::shared_ptr<BFComponentSystem> Ptr;

		CINJECT(BFComponentSystem(std::shared_ptr<BFApplication> application));
		virtual ~BFComponentSystem() noexcept = default;

		virtual void onEvent(const sdl::Event& ev) = 0;
		virtual void update(float dt) = 0;

	private:
		void setWorld(BFWorld* world);

	protected:
		std::shared_ptr<BFApplication> m_application;
		BFWorld* m_world;
	};
}

#endif