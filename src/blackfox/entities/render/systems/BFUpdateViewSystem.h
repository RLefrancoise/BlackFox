#pragma once

#include <cinject/cinject.h>

#include "BFComponentSystem.h"
#include "BFComponentSystemMacros.h"
#include "BFRenderSystem.h"

namespace BlackFox::Systems
{
    /*!
     * This system updates View components. Basically, it converts world units to pixels, so RenderSystem can use them.
     */
    class BLACKFOX_EXPORT BFUpdateViewSystem final: public BFComponentSystemBase<BFUpdateViewSystem, BeforeSystems<BFRenderSystem>>
    {
        BF_SYSTEM_AUTO_CREATE(BFUpdateViewSystem, ComponentSystemGroups::Render, "UpdateViewSystem")
        //BF_BEFORE_SYSTEM(BFRenderSystem)

    public:
        CINJECT(BFUpdateViewSystem(std::shared_ptr<BFApplication> app, std::shared_ptr<BFWorld> world));
        ~BFUpdateViewSystem() override = default;

        void update(float dt) override;
    };
}