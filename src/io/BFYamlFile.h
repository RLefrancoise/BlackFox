#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>

#include "BFDebug.h"

namespace BlackFox
{
	template <class T>
	struct BFYamlFile
	{		
		using Super = BFYamlFile<T>;

		BFYamlFile() = default;
		explicit BFYamlFile(const std::filesystem::path& path) : m_filePath(path) {}
		virtual ~BFYamlFile() = default;
		BFYamlFile(const BFYamlFile&) = default;
		BFYamlFile& operator=(const BFYamlFile&) = default;
		BFYamlFile(BFYamlFile&&) = default;
		BFYamlFile& operator=(BFYamlFile&&) = default;
		
		static T load(const std::filesystem::path& file)
		{
			const auto f = YAML::LoadFile(file.string());
			auto res = f.as<T>();
			res.m_filePath = file;
			return res;
		}

		static bool tryLoad(const std::string& file, std::shared_ptr<T>& data)
		{
			try
			{
				data = std::make_shared<T>(load(file));
				return true;
			}
			catch(const std::exception& err)
			{
				BF_ERROR(err.what());
				return false;
			}
		}
		
		[[nodiscard]] bool save() const
		{
			YAML::Emitter out;
			out << static_cast<const T&>(*this);
			
			std::ofstream ofs(m_filePath);
			if (!ofs.is_open()) return false;
			
			ofs << out.c_str();
			ofs.close();

			return ofs.good();
		}

		void saveOrThrow() const
		{
			if(!save())
			{
				BF_EXCEPTION("Failed to save YAML file {}", m_filePath.string());
			}
		}

		static void revertToFile(T& data)
		{
			const auto beforeRestore = static_cast<std::string>(data);
			data = load(data.m_filePath);
			BF_PRINT("Restored to file\nbefore -> {}\nafter -> {}", beforeRestore, static_cast<std::string>(data));
		}

		virtual explicit operator std::string() const = 0;

		const std::filesystem::path& file() const { return m_filePath; }

	private:
		std::filesystem::path m_filePath;
	};
}