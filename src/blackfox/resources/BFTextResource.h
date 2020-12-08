#pragma once

#include <SFML/System/String.hpp>
#include "BFResource.h"

namespace BlackFox
{
	class BLACKFOX_EXPORT BFTextResource : public BFResource<BFTextResource>
	{
	public:
		explicit BFTextResource(const Resources::ResourceType& type, const ResourceGuid& guid);
		~BFTextResource() override = default;

		BFTextResource(BFTextResource&&) noexcept;
		BFTextResource& operator=(BFTextResource&&) noexcept;

		[[nodiscard]] virtual bool load(
				BFVirtualFileInputStream& stream,
				std::string* errorMessage) override;
		
		virtual void content(const std::string& content);
		[[nodiscard]] virtual std::string content() const;

	protected:
		sf::String m_content;
	};
}
