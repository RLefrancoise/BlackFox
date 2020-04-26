#pragma once
#include <filesystem>

#include "BFResourceTypes.h"

namespace BlackFox
{
	/**
	 * Interface for any BlackFox resource.
	 */
	struct IBFResource
	{
		virtual ~IBFResource() = default;

		/**
		 * Get the type of the resource.
		 * 
		 * \return The type of the resource.
		 */
		[[nodiscard]] virtual const ResourceType& type() const = 0;
		
		/**
		 * Get the file representing the resource.
		 * 
		 * \return The file representing the resource.
		 */
		[[nodiscard]] virtual const std::filesystem::path& file() const = 0;

		/**
		 * Save the resource on disk.
		 * 
		 * \return True if save is successful, false otherwise.
		 */
		[[nodiscard]] virtual bool save() const = 0;

		/**
		 * Save the resource on disk, and throw if an error occured.
		 * 
		 */
		virtual void saveOrThrow() const = 0;

		/**
		 * Load the resource from a file.
		 * 
		 * \param	file	File to load the resource
		 * \param	errorMessage	Error message if load failed
		 * \return	True if load is successful, false otherwise. 
		 */
		[[nodiscard]] virtual bool load(const std::filesystem::path& file, std::string* errorMessage = nullptr) = 0;

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
	struct BFResource : IBFResource
	{
		virtual ~BFResource() = default;
		BFResource(const BFResource&) = default;
		BFResource& operator=(const BFResource&) = default;
		BFResource(BFResource&&) = default;
		BFResource& operator=(BFResource&&) = default;

		[[nodiscard]] const ResourceType& type() const override;
		[[nodiscard]] const std::filesystem::path& file() const override;
		void saveOrThrow() const override;
		void loadOrThrow(const std::filesystem::path& file) override;
		
	protected:
		explicit BFResource(const ResourceType& type, std::filesystem::path file);

		ResourceType m_type;
		std::filesystem::path m_filePath;
	};
}
