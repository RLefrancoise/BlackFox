#pragma once

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"

namespace BlackFox::Systems
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// Sort By Depth System, from the lowest to the highest.
	/// </summary>
	/// --------------------------------------------------------------------------------
	class BFSortByDepthSystem : public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFSortByDepthSystem, ComponentSystemGroups::Render, "SortByDepthSystem")

	public:
		CINJECT(BFSortByDepthSystem(std::shared_ptr<BFApplication> application));
		void update(float dt) override;
	};
}