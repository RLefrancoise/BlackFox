#pragma once

#include <string>
#include <fstream>

#include "BFExport.h"

namespace BlackFox
{
    /*!
     * Component system group
     */
	enum class ComponentSystemGroups
	{
	    /// Game Loop
		GameLoop		= 1,
		/// Render
		Render			= 2,
		/// End of frame
		EndOfFrame		= 3,
		/// Fixed time
		FixedTime		= 4,
		/// Unknown
		Unknown			= 0
	};

	/*!
	 * Convert component system group to string
	 *
	 * @param group     Group to convert
	 * @return          String representation
	 */
	BLACKFOX_EXPORT std::string toString(const ComponentSystemGroups& group);
}

BLACKFOX_EXPORT std::ostream& operator<<(std::ostream& stream, const BlackFox::ComponentSystemGroups& group);