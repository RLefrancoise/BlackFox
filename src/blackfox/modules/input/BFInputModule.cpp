#include "BFInputModule.h"
#include "BFInputModuleInstaller.h"

namespace BlackFox::Input
{
    BFInputModule::BFInputModule(BlackFox::DiContainer container)
    : BFApplicationModule(std::move(container))
    {}

    void BFInputModule::install(const BlackFox::DiContext &context)
    {
        context->addInstaller(std::make_shared<BFInputModuleInstaller>(m_container));
    }

    void BFInputModule::onInit()
    {
        BFApplicationModule::onInit();

        m_input = m_container->get<BFInput>();
    }

    void BFInputModule::onEvent(const std::vector<sf::Event>& event)
    {
        BFApplicationModule::onEvent(event);

        m_input->updateEvents(event);
    }
}