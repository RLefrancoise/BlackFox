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
    BFColor BLACKFOX_EXPORT lerp(const BFColor& min, const BFColor& max, float t);
}