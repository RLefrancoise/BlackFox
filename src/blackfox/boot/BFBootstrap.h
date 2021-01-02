#pragma once

#include "IBFContext.h"
#include "IBFApplicationModule.h"
#include "BFGame.h"

namespace BlackFox
{
	class BFBootstrap
	{
	public:
		constexpr BFBootstrap() = default;
		~BFBootstrap() = default;
		BFBootstrap(BFBootstrap&& bootstrap) noexcept;
		BFBootstrap& operator=(BFBootstrap&& bootstrap) noexcept;
		
		constexpr BFBootstrap(const BFBootstrap& app) = delete;
		constexpr BFBootstrap& operator=(const BFBootstrap& app) = delete;

		template<class Game = IBFGame>
		[[nodiscard]] int run(int argc, char** argv);

	private:
	    /// DI container
	    DiContainer m_container;
	    /// DI context
	    DiContext m_context;

	    /*!
	     * Load a module
	     *
	     * @tparam Module Module type
	     */
	    template<class Module = IBFApplicationModule>
	    void loadModule() const;
	};
}

#include "BFBootstrap.inl"
