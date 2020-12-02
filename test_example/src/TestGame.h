#pragma once

#include "BFGame.h"

namespace TestExample
{
    class TestGame : public BlackFox::BFGame
    {
    public:
        CINJECT(TestGame(BlackFox::DiContainer container, BlackFox::BFApplication::Ptr application));

        void onInit() override;
        void onShutdown() override;

        void onLoadLevel() override;
        void onUnloadLevel() override;

        void onUpdate(float dt) override;
        void onFixedUpdate() override;
    };
}