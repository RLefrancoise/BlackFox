#pragma once

#include "BFResourcesHolder.h"

namespace BlackFox::Editor
{
    class BFDataManager;

    class BFEditorResourcesHolder final : public BFResourcesHolderBase
    {
    public:
        CINJECT(BFEditorResourcesHolder());
        ~BFEditorResourcesHolder() override = default;

        BFEditorResourcesHolder(BFEditorResourcesHolder&& holder) noexcept = default;
        BFEditorResourcesHolder& operator=(BFEditorResourcesHolder&& holder) noexcept = default;

    protected:
        BFTextResource::Handle createTextAssetHandle(entt::id_type id, const ResourceGuid& guid, const Resources::ResourceType& type) override;
        TextureHandle createTextureHandle(entt::id_type id, const ResourceGuid& guid, const sf::IntRect& rect) override;
        FontHandle createFontHandle(entt::id_type id, const ResourceGuid& guid) override;
    };
}