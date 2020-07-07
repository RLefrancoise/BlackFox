#pragma once

#include <memory>
#include <vector>
#include <SFML/Window/Event.hpp>

#include "BFExport.h"
#include "BFTypeDefs.h"
#include "IBFContext.h"

namespace BlackFox
{
    /*!
     * Interface for BlackFox module
     */
    class BLACKFOX_EXPORT IBFApplicationModule
    {
    public:
        typedef std::shared_ptr<IBFApplicationModule> Ptr;

        virtual ~IBFApplicationModule() = default;

        virtual void onInit() = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onFixedUpdate(float dt) = 0;
        virtual void onEvent(const std::vector<sf::Event>& events) = 0;
        virtual void onRender(float dt) = 0;
        virtual void onEndOfFrame(float dt) = 0;
        virtual void onDestroy() = 0;

        /*!
         * Install the module to the given context
         *
         * @param context   Context to use to install the module
         */
        virtual void install(const DiContext& context) = 0;
    };

    /*!
     * Base class for BlackFox module
     */
    class BLACKFOX_EXPORT BFApplicationModule : public IBFApplicationModule
    {
    public:
        void onInit() override;
        void onUpdate(float dt) override;
        void onFixedUpdate(float dt) override;
        void onEvent(const std::vector<sf::Event>& events) override;
        void onRender(float dt) override;
        void onEndOfFrame(float dt) override;
        void onDestroy() override;

    protected:
        explicit BFApplicationModule(DiContainer container);

        /// DI container to install the module
        DiContainer m_container;
    };
}