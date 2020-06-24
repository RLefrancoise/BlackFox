#pragma once

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox::Utils
{
    /*!
     * Lerp a color from a color to another
     *
     * @param min   Start color
     * @param max   End color
     * @param t     Lerp value
     * @return      The color after the lerp
     */
    BLACKFOX_EXPORT BFColor lerp(const BFColor& min, const BFColor& max, float t);

    /*!
	 * Get a color from a string
	 *
	 * @param str	String to transform to a string. Format is [0-255],[0-255],[0-255],[0-255]
	 *
	 * @return		Color
	 */
    BLACKFOX_EXPORT BFColor colorFromString(const std::string& str);

    /*!
     * Transform a color to a string
     *
     * @param color	The color to transform to a string
     *
     * @return		A string in the format [0-255],[0-255],[0-255],[0-255]
     */
    BLACKFOX_EXPORT std::string colorToString(const BFColor& color);
}