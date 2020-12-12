#include "TestGame.h"
#include "BFScriptingManager.h"

using namespace BlackFox;

namespace TestExample
{
    TestGame::TestGame(DiContainer container, BFApplication::Ptr application)
    : BFGame(std::move(container), std::move(application))
    {}

    void TestGame::onInit()
    {
        //Launch test script
        const auto scriptManager = m_container->get<BFScriptingManager>();
        BF_PRINT("Test.lua result: {}", scriptManager->evalFile<bool>("data/test.lua"));
    }

    void TestGame::onShutdown() {}

    void TestGame::onLoadLevel() {}
    void TestGame::onUnloadLevel() {}

    void TestGame::onUpdate(float dt) {}
    void TestGame::onFixedUpdate() {}
}