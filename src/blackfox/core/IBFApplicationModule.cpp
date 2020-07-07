#include "IBFApplicationModule.h"

namespace BlackFox
{
    BFApplicationModule::BFApplicationModule(BlackFox::DiContainer container)
    : m_container(std::move(container))
    {}

    void BFApplicationModule::onInit() {}
    void BFApplicationModule::onUpdate(float dt) {}
    void BFApplicationModule::onFixedUpdate(float dt) {}
    void BFApplicationModule::onEvent(const std::vector<sf::Event> &events) {}
    void BFApplicationModule::onRender(float dt) {}
    void BFApplicationModule::onEndOfFrame(float dt) {}
    void BFApplicationModule::onDestroy() {}
}