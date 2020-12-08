#include "BFIniFile.h"
#include "BFDebug.h"

namespace BlackFox
{
    BFIniFile::BFIniFile(const std::filesystem::path& path)
    {
        m_reader = INIReader(path.string());
        if (m_reader.ParseError() == -1)
            BF_EXCEPTION("Failed to open INI file {}", path.string());
        if (m_reader.ParseError() > 0)
            BF_EXCEPTION("Parse error in INI file {} at line {}", path.string(), m_reader.ParseError());
    }

    std::string BFIniFile::get(const std::string& section, const std::string& key, const std::string& defaultValue) const
    {
        return m_reader.Get(section, key, defaultValue);
    }

    int BFIniFile::getInt(const std::string& section, const std::string& key, int defaultValue) const
    {
        return m_reader.GetInteger(section, key, defaultValue);
    }

    bool BFIniFile::getBool(const std::string& section, const std::string& key, bool defaultValue) const
    {
        return m_reader.GetBoolean(section, key, defaultValue);
    }

    float BFIniFile::getFloat(const std::string& section, const std::string& key, float defaultValue) const
    {
        return m_reader.GetFloat(section, key, defaultValue);
    }

    double BFIniFile::getDouble(const std::string& section, const std::string& key, double defaultValue) const
    {
        return m_reader.GetReal(section, key, defaultValue);
    }
}