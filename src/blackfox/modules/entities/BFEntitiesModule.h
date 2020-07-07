#pragma once

#include "IBFApplicationModule.h"

namespace BlackFox::Entities
{
    class BLACKFOX_EXPORT BFEntitiesModule : public BFApplicationModule
    {
    public:
        explicit BFEntitiesModule(DiContainer container);
        void install(const DiContext& context) override;

        void onInit() override;
        void onUpdate(float dt) override;
        void onFixedUpdate(float dt) override;
        void onRender(float dt) override;
        void onEndOfFrame(float dt) override;
    };
}