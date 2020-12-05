#pragma once

#include <filesystem>
#include <SFML/System/String.hpp>

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
		
		/**
		 * Save the resource on disk.
		 * 
		 * \return True if save is successful, false otherwise.
		 */
		[[nodiscard]] virtual bool save() const = 0;

		/**
		 * Save the resource on disk, and throw if an error occured.
		 */
		virtual void saveOrThrow() const = 0;

		/**
		 * Load the resource from a file.
		 * 
		 * \param	file	File to load the resource
		 * \param	errorMessage	Error message if load failed
		 * \return	True if load is successful, false otherwise. 
		 */
		[[nodiscard]] virtual bool load(const std::filesystem::path& file, std::string* errorMessage) = 0;

		/**
		 * Load the resource from a file, and throw if an error occured.
		 * 
		 * \param file	File to load the resource
		 */
		virtual void loadOrThrow(const std::filesystem::path& file) = 0;
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

		constexpr BFResource(BFResource&&) noexcept;
		constexpr BFResource& operator=(BFResource&&) noexcept;

		[[nodiscard]] constexpr const Resources::ResourceType& type() const override;

		[[nodiscard]] constexpr ResourceGuid guid() const override;

		void saveOrThrow() const override;

		[[nodiscard]] bool load(const std::filesystem::path& file, std::string* errorMessage) override;
		void loadOrThrow(const std::filesystem::path& file) override;
		
	protected:
		constexpr explicit BFResource(const Resources::ResourceType& type, const ResourceGuid& guid);

		Resources::ResourceType m_type;
		ResourceGuid m_guid;
	};
}

#include "BFResource.inl"