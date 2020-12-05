#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

#include "BFDebug.h"
#include "BFTextResource.h"

namespace BlackFox
{
	class BFYamlFile : public BFTextResource
	{
	public:
		explicit BFYamlFile(const Resources::ResourceType& type, const ResourceGuid& guid);

		~BFYamlFile() override = default;
		BFYamlFile(BFYamlFile&&) noexcept = default;
		BFYamlFile& operator=(BFYamlFile&&) noexcept = default;

		bool load(const std::filesystem::path& file, std::string* errorMessage) override;

		template<class T>
		inline void from(const T& from)
		{
		    YAML::Emitter out;
		    out << from;

		    content(out.c_str());
		}

		template<class T>
		inline void to(T* to) const
		{
			*to = m_root.as<T>();
		}

		void content(const std::string& content) override;

	protected:
	    YAML::Node m_root;
	};
}