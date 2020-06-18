#include "BFResource.h"
#include "BFDebug.h"

namespace BlackFox
{
	const Resources::ResourceType& BFResource::type() const
	{
		return m_type;
	}

	const std::filesystem::path& BFResource::file() const
	{
		return m_filePath;
	}

	void BFResource::file(const std::filesystem::path& file)
	{
		m_filePath = file;
	}

	void BFResource::saveOrThrow() const
	{
		if (!save())
		{
			BF_EXCEPTION("Failed to save resource {}", m_filePath.string());
		}
	}

	bool BFResource::load(const std::filesystem::path& file, std::string* errorMessage)
	{
		m_filePath = file;
		return true;
	}

	void BFResource::loadOrThrow(const std::filesystem::path& file)
	{
		std::string err;
		if (!load(file, &err))
		{
			BF_EXCEPTION("Failed to load resource {}: {}", file.string(), err);
		}
	}

	BFResource::BFResource(const Resources::ResourceType& type) 
	: m_type(type)
	{
	}
}
