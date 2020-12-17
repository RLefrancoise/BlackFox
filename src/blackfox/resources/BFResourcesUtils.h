#pragma once

#include "BFTypeDefs.h"
#include "BFDebug.h"

namespace BlackFox
{
    static inline ResourceGuid generateNewGuid()
    {
        return uuids::uuid_system_generator{}();
    }
}