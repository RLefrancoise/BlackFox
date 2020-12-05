#include "BFYamlFile.h"

namespace BlackFox
{
    BFYamlFile::BFYamlFile(const Resources::ResourceType& type, const ResourceGuid& guid)
    : BFTextResource(type, guid)
    {}

    bool BFYamlFile::load(const std::filesystem::path& file, std::string* errorMessage)
    {
        try
        {
            if (!BFTextResource::load(file, errorMessage))
                throw std::runtime_error(errorMessage ? errorMessage->c_str() : "Failed to load YAML file");

            m_root = YAML::LoadFile(file.string());
        }
        catch(const std::exception& err)
        {
            if (errorMessage) *errorMessage = err.what();
            return false;
        }

        return true;
    }

    void BFYamlFile::content(const std::string& content)
    {
        BFTextResource::content(content);
        m_root = YAML::Load(m_content);
    }
}