#include "BFGame.h"

namespace BlackFox
{
    BFGame::BFGame(DiContainer container, BFApplication::Ptr application)
    : m_container(std::move(container))
    , m_application(std::move(application))
    {}

    BFGame::BFGame(BFGame &&game) noexcept
    : m_container(std::exchange(game.m_container, nullptr))
    , m_application(std::exchange(game.m_application, nullptr))
    {}
    
    BFGame& BFGame::operator=(BFGame &&game) noexcept
    {
        if(this != &game)
        {
            m_container = std::exchange(game.m_container, nullptr);
            m_application = std::exchange(game.m_application, nullptr);
        }

        return *this;
    }
}