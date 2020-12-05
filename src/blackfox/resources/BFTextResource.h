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

		BFTextResource(const BFTextResource&) = default;
		BFTextResource& operator=(const BFTextResource&) = default;
		BFTextResource(BFTextResource&&) noexcept;
		BFTextResource& operator=(BFTextResource&&) noexcept;
		
		[[nodiscard]] bool save() const override;

		[[nodiscard]] bool load(const std::filesystem::path& file, std::string* errorMessage) override;
		
		virtual void content(const std::string& content);
		[[nodiscard]] virtual std::string content() const;

	protected:
		sf::String m_content;
	};
}
