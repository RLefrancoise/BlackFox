#include "BFResource.h"
#include "BFDebug.h"

namespace BlackFox
{
	const ResourceType& BFResource::type() const
	{
		return m_type;
	}

	const std::filesystem::path& BFResource::file() const
	{
		return m_filePath;
	}

	void BFResource::saveOrThrow() const
	{
		if (!save())
		{
			BF_EXCEPTION("Failed to save resource {}", m_filePath.string());
		}
	}

	void BFResource::loadOrThrow(const std::filesystem::path& file)
	{
		if (!load(file))
		{
			BF_EXCEPTION("Failed to load resource {}", file.string());
		}
	}

	BFResource::BFResource(const ResourceType& type, std::filesystem::path file) : m_type(type), m_filePath(std::move(file))
	{
	}
}
