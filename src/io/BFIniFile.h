#ifndef BLACKFOX_INIFILE_H
#define BLACKFOX_INIFILE_H

#include <INIReader.h>

#include "BFDebug.h"

namespace BlackFox
{
    class BFIniFile
    {
    public:
        explicit BFIniFile(const std::string& fileName);

        std::string get(const std::string& section, const std::string& key, const std::string& defaultValue) const;
        int getInt(const std::string& section, const std::string& key, int defaultValue = 0) const;
        bool getBool(const std::string& section, const std::string& key, bool defaultValue = false) const;
        float getFloat(const std::string& section, const std::string& key, float defaultValue = 0.0f) const;
        double getDouble(const std::string& section, const std::string& key, double defaultValue = 0.0) const;
    private:
        INIReader m_reader;
    };
}

#endif //BLACKFOX_INIFILE_H
