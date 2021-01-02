#include "BFBootstrap.h"

namespace BlackFox
{
    BFBootstrap::BFBootstrap(BFBootstrap&& bootstrap) noexcept
    : m_container(std::exchange(bootstrap.m_container, nullptr))
    , m_context(std::exchange(bootstrap.m_context, nullptr))
    {
    }

    BFBootstrap& BFBootstrap::operator=(BFBootstrap&& bootstrap) noexcept
    {
        if(this != &bootstrap)
        {
            m_container = std::exchange(bootstrap.m_container, nullptr);
            m_context = std::exchange(bootstrap.m_context, nullptr);
        }

        return *this;
    }
}