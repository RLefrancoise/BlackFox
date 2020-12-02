#pragma once

#include "BFApplication.h"
#include "BFMainContext.h"
#include "BFDebug.h"

#include "BFInputModule.h"
#include "BFEntitiesModule.h"
#include "BFGraphicsModule.h"
#include "BFScriptingModule.h"

#include <rttr/library.h>

namespace BlackFox
{
    template<class Game>
    int BFBootstrap::run(int argc, char** argv)
    {
        try
        {
#ifdef BLACKFOX_SHARED_LIB
            //Load blackfox dll
            rttr::library lib("blackfox");
            if(!lib.load())
            {
                BF_EXCEPTION("Failed to load blackfox library: {}", lib.get_error_string().to_string());
            }

            //Load blackfox.physics dll
            rttr::library physicsLib("blackfox.physics");
            if(!physicsLib.load())
            {
                BF_EXCEPTION("Failed to load blackfox.physics library: {}", physicsLib.get_error_string().to_string());
            }

            //Load blackfox.graphics dll
            rttr::library graphicsLib("blackfox.graphics");
            if(!graphicsLib.load())
            {
                BF_EXCEPTION("Failed to load blackfox.graphics library: {}", graphicsLib.get_error_string().to_string());
            }

            //Load blackfox.scripting dll
            rttr::library scriptingLib("blackfox.scripting");
            if(!scriptingLib.load())
            {
                BF_EXCEPTION("Failed to load blackfox.scripting library: {}", scriptingLib.get_error_string().to_string());
            }
#endif

            //Create DI Container
            m_container = std::make_shared<cinject::Container>();
            m_container->bind<cinject::Container>().toConstant(m_container);

            //Create main context
            m_context = makeContext<BFMainContext>(m_container);

            //load modules
            loadModule<Input::BFInputModule>();
            loadModule<Entities::BFEntitiesModule>();
            loadModule<Graphics::BFGraphicsModule>();
            loadModule<Scripting::BFScriptingModule>();

            //Run context
            m_context->run();

            //Game
            m_container->bind<IBFGame>().to<Game>().inSingletonScope();

            //Execute the app
            const auto app = m_container->get<BFApplication>();
            if(!app->init(argc, argv))
            {
                BF_EXCEPTION("Failed to init application");
            }

            return app->execute();
        }
        catch(const std::exception& err)
        {
            BF_ERROR("{}", err.what());
            return EXIT_FAILURE;
        }
    }


    template<class Module>
    void BFBootstrap::loadModule() const
    {
        auto module = std::make_shared<Module>(m_container);
        m_container->bind<IBFApplicationModule>().toConstant(module);
        module->install(m_context);
    }
}