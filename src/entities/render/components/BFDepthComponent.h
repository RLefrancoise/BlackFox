#pragma once

#include "BFComponent.h"

namespace BlackFox::Components
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// Depth component
	/// </summary>
	/// --------------------------------------------------------------------------------
	struct BFDepthComponent final : IBFComponent
	{
		BF_COMPONENT("Depth")

		/// <summary>Depth value</summary>
		int depth;
	};
}