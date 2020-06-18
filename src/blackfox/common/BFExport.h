#pragma once

#if defined(WIN32)

#if defined(BLACKFOX_SHARED_LIB)
    #if defined(BLACKFOX_SHARED_LIB_EXPORT)
        #define BLACKFOX_EXPORT __declspec(dllexport)
    #else
        #define BLACKFOX_EXPORT __declspec(dllimport)
    #endif
#else
    #define BLACKFOX_EXPORT
#endif

#else

#define BLACKFOX_EXPORT

#endif
