#pragma once

#include <memory>

#include "BFExport.h"
#include "BFTypeDefs.h"

namespace BlackFox::Scripting
{
    /*!
     * Interface for language module
     */
    class BLACKFOX_EXPORT IBFLanguageModule
    {
    public:
        typedef std::shared_ptr<IBFLanguageModule> Ptr;

        virtual ~IBFLanguageModule() = default;

        /*!
         * Register the module
         */
        virtual void registerModule() = 0;
    };

    /*!
     * Base class for language module
     */
    class BLACKFOX_EXPORT BFLanguageModule : public IBFLanguageModule
    {
    protected:
        explicit BFLanguageModule(const char* name, DiContainer container);

        /// Module name
        const char* m_name;

        /// DI container
        DiContainer m_container;
    };
}