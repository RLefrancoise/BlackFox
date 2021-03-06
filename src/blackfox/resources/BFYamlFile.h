#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

#include "BFDebug.h"
#include "BFTextResource.h"

namespace BlackFox
{
	template <class T>
	class BFYamlFile : public BFTextResource
	{
	public:
		using Super = BFYamlFile<T>;

		explicit BFYamlFile(const Resources::ResourceType& type) : BFTextResource(type) {}

		~BFYamlFile() override = default;
		BFYamlFile(const BFYamlFile&) = default;
		BFYamlFile& operator=(const BFYamlFile&) = default;
		BFYamlFile(BFYamlFile&&) noexcept = default;
		BFYamlFile& operator=(BFYamlFile&&) noexcept = default;

		bool load(const std::filesystem::path& file, std::string* errorMessage) override
		{
			try
			{
				if (!BFTextResource::load(file, errorMessage)) throw std::runtime_error(errorMessage ? errorMessage->c_str() : "Failed to load YAML file");

				const auto f = YAML::LoadFile(file.string());
				auto res = f.as<T>();
				res.m_filePath = file.string();

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

		void content(const std::string& content) override
		{
			BF_EXCEPTION("Don't set content for YAML file with content method. Modify the object instance directly");
		}

		[[nodiscard]] std::string content() const override
		{
			YAML::Emitter out;
			out << static_cast<const T&>(*this);

			return out.c_str();
		}

		/*static void revertToFile(T& data)
		{
			const auto beforeRestore = static_cast<std::string>(data);
			data = load(data.m_filePath);
			BF_PRINT("Restored to file\nbefore -> {}\nafter -> {}", beforeRestore, static_cast<std::string>(data));
		}*/

		virtual explicit operator std::string() const = 0;
	};
}