#pragma once

#include <memory>
#include <cinject/cinject.h>

#include "BFExport.h"
#include "BFTypeDefs.h"
#include "BFApplication.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT IBFGame
    {
    public:
        typedef std::shared_ptr<IBFGame> Ptr;

        IBFGame(const IBFGame&) = delete;
        IBFGame& operator=(const IBFGame&) = delete;

        constexpr IBFGame() = default;
        virtual ~IBFGame() = default;

        virtual void onInit() = 0;
        virtual void onShutdown() = 0;

        virtual void onLoadLevel() = 0;
        virtual void onUnloadLevel() = 0;

        virtual void onUpdate(float dt) = 0;
        virtual void onFixedUpdate() = 0;
    };

    class BLACKFOX_EXPORT BFGame : public IBFGame
    {
    protected:

        BFGame(DiContainer container, BFApplication::Ptr application);

        BFGame(BFGame&& game) noexcept;
        BFGame& operator=(BFGame&& game) noexcept;

        DiContainer m_container;
        BFApplication::Ptr m_application;
    };
}