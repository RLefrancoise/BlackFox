#pragma once

#include <cinject/cinject.h>
#include <memory>
#include <vector>

#include "BFExport.h"
#include "BFTypeDefs.h"
#include "IBFLanguageModule.h"

namespace BlackFox::Scripting
{
    /*!
     * BlackFox interface for scripting language
     */
    class BLACKFOX_EXPORT IBFScriptingLanguage
    {
    public:
        typedef std::shared_ptr<IBFScriptingLanguage> Ptr;

        virtual ~IBFScriptingLanguage() = default;

        /*!
         * Add a module to the language
         *
         * @param module    Module to add
         */
        virtual void addModule(IBFLanguageModule::Ptr module) = 0;

        /*!
         * Use the language
         */
        virtual void use() = 0;
    };

    /*!
     * Base class for scripting language
     */
    class BLACKFOX_EXPORT BFScriptingLanguage : public IBFScriptingLanguage
    {
    public:
        void use() override;
        void addModule(IBFLanguageModule::Ptr module) override;

    protected:
        explicit BFScriptingLanguage(DiContainer container);

        /// DI container
        DiContainer m_container;

        /// Language modules
        std::vector<IBFLanguageModule::Ptr> m_modules;
    };
}