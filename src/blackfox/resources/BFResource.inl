#include "BFResource.h"
#include "BFDebug.h"

namespace BlackFox
{
	template<class T>
	constexpr BFResource<T>::BFResource(const Resources::ResourceType& type, const ResourceGuid& guid)
			: m_type(type)
			, m_guid(guid)
	{}

    template<class T>
	constexpr BFResource<T>::BFResource(BFResource<T> && res) noexcept
	: m_type(std::exchange(res.m_type, Resources::UNKNOWN_TYPE))
	, m_guid(std::exchange(res.m_guid, ResourceGuid()))
	{}

	template<class T>
	constexpr BFResource<T> &BFResource<T>::operator=(BFResource<T> && res) noexcept
	{
		if(this != &res)
		{
			m_type = std::exchange(res.m_type, Resources::UNKNOWN_TYPE);
			m_guid = std::exchange(res.m_guid, ResourceGuid());
		}

		return *this;
	}

	template<class T>
	inline constexpr const Resources::ResourceType& BFResource<T>::type() const
	{
		return m_type;
	}

	template<class T>
	inline constexpr ResourceGuid BFResource<T>::guid() const
	{
		return m_guid;
	}

	template<class T>
	inline void BFResource<T>::saveOrThrow() const
	{
		if (!save())
		{
			BF_EXCEPTION("Failed to save resource {}", m_guid.data());
		}
	}

	template<class T>
	inline bool BFResource<T>::load(const std::filesystem::path& file, std::string* errorMessage)
	{
		m_guid = Resources::pathToGuid(file);
		return true;
	}

	template<class T>
	inline void BFResource<T>::loadOrThrow(const std::filesystem::path& file)
	{
		std::string err;
		if (!load(file, &err))
		{
			BF_EXCEPTION("Failed to load resource {}: {}", file.string(), err);
		}
	}
}
