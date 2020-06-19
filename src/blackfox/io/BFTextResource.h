#pragma once

#include "BFResource.h"

namespace BlackFox
{
	struct BLACKFOX_EXPORT BFTextResource : BFResource
	{
		explicit BFTextResource(const Resources::ResourceType& type);

		~BFTextResource() override = default;

		BFTextResource(const BFTextResource&) = default;
		BFTextResource& operator=(const BFTextResource&) = default;
		BFTextResource(BFTextResource&&) = default;
		BFTextResource& operator=(BFTextResource&&) = default;
		
		[[nodiscard]] bool save() const override;

		[[nodiscard]] bool load(const std::filesystem::path& file, std::string* errorMessage) override;
		
		virtual void content(const std::string& content);
		[[nodiscard]] virtual std::string content() const;

	protected:
		std::string m_content;
	};
}
