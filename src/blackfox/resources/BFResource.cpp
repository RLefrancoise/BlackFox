#include "BFResource.h"
#include "BFDebug.h"

namespace BlackFox
{
	BFResource::BFResource(BFResource && res) noexcept
	: m_type(res.m_type)
	, m_filePath(res.m_filePath)
	{}

	BFResource &BFResource::operator=(BFResource && res) noexcept
	{
		m_type = res.m_type;
		m_filePath = res.m_filePath;
		return *this;
	}

	BFResource::BFResource(const Resources::ResourceType& type)
	: m_type(type)
	{}

	const Resources::ResourceType& BFResource::type() const
	{
		return m_type;
	}

	std::filesystem::path BFResource::file() const
	{
		return static_cast<std::string>(m_filePath);
	}

	void BFResource::file(const std::filesystem::path& file)
	{
		m_filePath = file.string();
	}

	void BFResource::saveOrThrow() const
	{
		if (!save())
		{
			BF_EXCEPTION("Failed to save resource {}", static_cast<std::string>(m_filePath));
		}
	}

	bool BFResource::load(const std::filesystem::path& file, std::string* errorMessage)
	{
		m_filePath = file.string();
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
}
