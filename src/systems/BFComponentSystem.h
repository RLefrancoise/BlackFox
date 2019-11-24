#ifndef BLACKFOX_COMPONENTSYSTEM_H
#define BLACKFOX_COMPONENTSYSTEM_H

#include "../core/BFLevel.h"

namespace BlackFox
{
	class BFComponentSystem
	{
	public:
		explicit BFComponentSystem(BFLevel::Ptr level);
		virtual ~BFComponentSystem() noexcept = default;

		virtual void update(float dt) = 0;

	protected:
		BFLevel::Ptr m_level;
	};
}

#endif