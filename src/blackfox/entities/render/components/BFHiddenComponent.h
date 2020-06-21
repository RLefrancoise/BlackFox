#pragma once

#include "BFComponent.h"

namespace BlackFox::Components
{
    /*!
     * Hidden component. Use to hide things on screen when this component is on an entity.
     */
    struct BLACKFOX_EXPORT BFHiddenComponent: IBFComponent
    {
        BF_COMPONENT("Hidden")
    };
}