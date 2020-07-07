#pragma once

#include "IBFContext.h"
#include "IBFApplicationModule.h"

namespace BlackFox
{
	class BFBootstrap
	{
	public:
		constexpr BFBootstrap() = default;
		~BFBootstrap() = default;
		BFBootstrap(BFBootstrap&& bootstrap) noexcept = default;
		BFBootstrap& operator=(BFBootstrap&& bootstrap) = default;
		
		constexpr BFBootstrap(const BFBootstrap& app) = delete;
		constexpr BFBootstrap& operator=(const BFBootstrap& app) = delete;

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
	    template<class Module>
	    void loadModule() const
        {
            auto module = std::make_shared<Module>(m_container);
            m_container->bind<IBFApplicationModule>().toConstant(module);
            module->install(m_context);
        }
	};
}
