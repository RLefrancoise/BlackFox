#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <utility>

#include "BFDebug.h"
#include "BFTextResource.h"

namespace BlackFox
{
	template <class T>
	struct BFYamlFile : BFTextResource
	{		
		using Super = BFYamlFile<T>;

		explicit BFYamlFile(const ResourceType& type, std::filesystem::path path) : BFTextResource(type, std::move(path)) {}
		virtual ~BFYamlFile() = default;
		BFYamlFile(const BFYamlFile&) = default;
		BFYamlFile& operator=(const BFYamlFile&) = default;
		BFYamlFile(BFYamlFile&&) = default;
		BFYamlFile& operator=(BFYamlFile&&) = default;

		bool load(const std::filesystem::path& file, std::string* errorMessage = nullptr) override
		{
			try
			{
				const auto f = YAML::LoadFile(file.string());
				auto res = f.as<T>();
				res.m_filePath = file;

				T* thisP = static_cast<T*>(this);
				*thisP = res;
			}
			catch(const std::exception& err)
			{
				if (errorMessage) *errorMessage = err.what();
				return false;
			}

			return true;
		}

		[[nodiscard]] std::string content() const override
		{
			YAML::Emitter out;
			out << static_cast<const T&>(*this);

			return out.c_str();
		}

		static void revertToFile(T& data)
		{
			const auto beforeRestore = static_cast<std::string>(data);
			data = load(data.m_filePath);
			BF_PRINT("Restored to file\nbefore -> {}\nafter -> {}", beforeRestore, static_cast<std::string>(data));
		}

		virtual explicit operator std::string() const = 0;
	};
}