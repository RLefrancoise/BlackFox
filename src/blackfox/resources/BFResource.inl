#include "BFResource.h"
#include "BFDebug.h"

namespace BlackFox
{
	template<class T>
	BFResource<T>::BFResource(const Resources::ResourceType& type, const ResourceGuid& guid)
	: m_type(type)
	, m_guid(guid)
	{}

    template<class T>
	BFResource<T>::BFResource(BFResource<T> && res) noexcept
	: m_type(std::exchange(res.m_type, Resources::UNKNOWN_TYPE))
	, m_guid(std::exchange(res.m_guid, ResourceGuid()))
	{}

	template<class T>
	BFResource<T> &BFResource<T>::operator=(BFResource<T> && res) noexcept
	{
		if(this != &res)
		{
			m_type = std::exchange(res.m_type, Resources::UNKNOWN_TYPE);
			m_guid = std::exchange(res.m_guid, ResourceGuid());
		}

		return *this;
	}

	template<class T>
	inline const Resources::ResourceType& BFResource<T>::type() const
	{
		return m_type;
	}

	template<class T>
	inline ResourceGuid BFResource<T>::guid() const
	{
		return m_guid;
	}

	/*template<class T>
	inline void BFResource<T>::saveOrThrow(IBFVirtualFileSystem::Ptr vfs) const
	{
		if (!save(vfs))
		{
			BF_EXCEPTION("Failed to save resource {}", Resources::guidToPath(m_guid).string());
		}
	}*/

	template<class T>
	inline void BFResource<T>::loadOrThrow(BFVirtualFileInputStream& stream)
	{
		std::string err;
		if (!load(stream, &err))
		{
			BF_EXCEPTION("Failed to load resource {}: {}", m_guid, err);
		}
	}
}
