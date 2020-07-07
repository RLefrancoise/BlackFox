#pragma once

#include <cinject/cinject.h>

#include "IBFApplicationModule.h"
#include "BFInput.h"

namespace BlackFox::Input
{
    /*!
     * BlackFox Input module
     */
    class BLACKFOX_EXPORT BFInputModule : public BFApplicationModule
    {
    public:
        explicit BFInputModule(DiContainer container);
        void install(const DiContext& context) override;
        void onInit() override;
        void onEvent(const std::vector<sf::Event>& event) override;

    private:
        BFInput::Ptr m_input;
    };
}