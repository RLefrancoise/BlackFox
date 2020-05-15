#pragma once
#include "BFResource.h"
#include <fstream>

namespace BlackFox
{
	struct BFTextResource : BFResource
	{
		explicit BFTextResource(const Resources::ResourceType& type) : BFResource(type) {}
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

		[[nodiscard]] bool load(const std::filesystem::path& file, std::string* errorMessage = nullptr) override
		{
			std::ifstream ifs(file);
			if (!ifs.is_open() || !ifs.good())
			{
				*errorMessage = "Failed to open file";
				return false;
			}

			const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
			m_content = str;

			ifs.close();

			return true;
		}
		
		virtual void content(const std::string& content)
		{
			m_content = content;
		}

		[[nodiscard]] virtual std::string content() const
		{
			return m_content;
		}

	protected:
		std::string m_content;
	};
}
