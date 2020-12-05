#pragma once

#include <INIReader.h>
#include "BFExport.h"
#include "BFTextResource.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFIniFile : public BFTextResource
    {
    public:
        explicit BFIniFile(const Resources::ResourceType& type, const ResourceGuid& guid);

        bool load(const std::filesystem::path& file, std::string* errorMessage) override;

        std::string get(const std::string& section, const std::string& key, const std::string& defaultValue) const;
        int getInt(const std::string& section, const std::string& key, int defaultValue = 0) const;

        template <typename T>
        T getIntTo(const std::string& section, const std::string& key, T defaultValue) const
        {
            return static_cast<T>(getInt(section, key, defaultValue));
        }

        bool getBool(const std::string& section, const std::string& key, bool defaultValue = false) const;
        float getFloat(const std::string& section, const std::string& key, float defaultValue = 0.0f) const;
        double getDouble(const std::string& section, const std::string& key, double defaultValue = 0.0) const;
    private:
        INIReader m_reader;
    };
}