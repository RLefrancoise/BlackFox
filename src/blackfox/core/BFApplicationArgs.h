#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

namespace BlackFox
{
    /*!
     * Arguments sent to the application through command line
     */
    class BFApplicationArgs
    {
    public:
        typedef std::shared_ptr<BFApplicationArgs> Ptr;
        typedef std::variant<std::string, int, bool> Argument;

        explicit BFApplicationArgs(int argc, char** argv);

        int argc() const;
        char** const argv() const;

        /*!
         * Base folder where to find resources etc...
         * @return The base folder
         */
        const std::string& baseFolder() const;

    private:
        int m_argc;
        char** const m_argv;
        std::unordered_map<std::string, Argument> m_arguments;
    };
}