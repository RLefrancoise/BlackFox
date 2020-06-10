#pragma once

#include <memory>

namespace BlackFox
{
    /*!
     * Blackfox service interface
     */
    class IBFService
    {
    public:
        typedef std::shared_ptr<IBFService> Ptr;

        virtual ~IBFService() = default;

        /*!
         * Run the service.
         */
        virtual void run() = 0;
    };
}
