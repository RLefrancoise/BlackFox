#pragma once

#include <filesystem>
#include <SFML/System/String.hpp>

#include "BFResourceTypes.h"

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
		
		/**
		 * Get the file representing the resource.
		 * 
		 * \return The file representing the resource.
		 */
		[[nodiscard]] virtual std::filesystem::path file() const = 0;

		/**
		 * Set the file representing the resource.
		 * 
		 * \param file	The file representing the resource.
		 */
		virtual void file(const std::filesystem::path& file) = 0;
		
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
	class BLACKFOX_EXPORT BFResource : public IBFResource
	{
	public:
		~BFResource() override = default;
		BFResource(const BFResource&) = default;
		BFResource& operator=(const BFResource&) = default;
		BFResource(BFResource&&) noexcept;
		BFResource& operator=(BFResource&&) noexcept;

		[[nodiscard]] const Resources::ResourceType& type() const override;
		[[nodiscard]] std::filesystem::path file() const override;
		void file(const std::filesystem::path& file) override;
		
		void saveOrThrow() const override;

		[[nodiscard]] bool load(const std::filesystem::path& file, std::string* errorMessage) override;
		void loadOrThrow(const std::filesystem::path& file) override;
		
	protected:
		explicit BFResource(const Resources::ResourceType& type);

		Resources::ResourceType m_type;
		//std::filesystem::path m_filePath;
		sf::String m_filePath;
	};
}
