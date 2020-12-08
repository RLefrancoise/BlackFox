#pragma once

#include <filesystem>
#include <SFML/System/String.hpp>

#include "BFVirtualFileInputStream.h"
#include "BFResourceTypes.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	/**
	 * Interface for any BlackFox resource.
	 */
	class BLACKFOX_EXPORT IBFResource
	{
	public:
		virtual ~IBFResource() = default;

		/**
		 * Get the type of the resource.
		 * 
		 * \return The type of the resource.
		 */
		[[nodiscard]] virtual const Resources::ResourceType& type() const = 0;

		/*!
		 * Get the Guid.
		 *
		 * @return	Guid
		 */
		[[nodiscard]] virtual ResourceGuid guid() const = 0;

		/*!
		 * Load the resource from a stream.
		 *
		 * @param stream		Stream
		 * @param errorMessage 	Error message if load failed
		 *
		 * @return				True if load successful, false otherwise
		 */
		[[nodiscard]] virtual bool load(
				BFVirtualFileInputStream& stream,
				std::string* errorMessage) = 0;

		/*!
		 * Load the resource from a stream, and throw if an error occurred.
		 * 
		 * @param stream		Stream
		 */
		virtual void loadOrThrow(BFVirtualFileInputStream& stream) = 0;
	};

	/**
	 * Base class for BlackFox resource.
	 */
	template<class T>
	class BLACKFOX_EXPORT BFResource : public IBFResource
	{
	public:
		typedef entt::resource_handle<T> Handle;
		using Super = BFResource<T>;

		~BFResource() override = default;

		BFResource(const BFResource&) = delete;
		BFResource& operator=(const BFResource&) = delete;

		BFResource(BFResource&&) noexcept;
		BFResource& operator=(BFResource&&) noexcept;

		[[nodiscard]] const Resources::ResourceType& type() const override;
		[[nodiscard]] ResourceGuid guid() const override;

		void loadOrThrow(BFVirtualFileInputStream& stream) override;
		
	protected:
		explicit BFResource(const Resources::ResourceType& type, const ResourceGuid& guid);

		Resources::ResourceType m_type;
		ResourceGuid m_guid;
	};
}

#include "BFResource.inl"