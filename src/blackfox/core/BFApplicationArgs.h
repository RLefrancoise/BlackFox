#pragma once

#include <SFML/System/String.hpp>
#include <memory>
#include "BFExport.h"

namespace BlackFox
{
    /*!
     * Struct representing the arguments sent to the application through command line
     */
    struct BLACKFOX_EXPORT BFApplicationArgs
    {
        typedef std::shared_ptr<BFApplicationArgs> Ptr;

        explicit BFApplicationArgs(int argc, char** argv);

        /// Base folder where to find resources etc...
        sf::String baseFolder;
    };
}