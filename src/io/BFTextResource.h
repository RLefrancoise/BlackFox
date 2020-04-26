#pragma once
#include "BFResource.h"

namespace BlackFox
{
	struct BFTextResource : BFResource
	{
		explicit BFTextResource(const ResourceType& type, const std::filesystem::path& file) : BFResource(type, file) {}
		virtual ~BFTextResource() = default;

		BFTextResource(const BFTextResource&) = default;
		BFTextResource& operator=(const BFTextResource&) = default;
		BFTextResource(BFTextResource&&) = default;
		BFTextResource& operator=(BFTextResource&&) = default;
		
		[[nodiscard]] bool save() const override
		{
			std::ofstream ofs(m_filePath);
			if (!ofs.is_open()) return false;

			ofs << content();
			ofs.close();

			return ofs.good();
		}

	protected:
		[[nodiscard]] virtual std::string content() const = 0;
	};
}
