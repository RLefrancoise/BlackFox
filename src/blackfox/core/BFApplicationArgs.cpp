#include "BFApplicationArgs.h"
#include "BFStringUtils.h"
#include "BFDebug.h"

#include <regex>
#include <vector>
#include <filesystem>

namespace BlackFox
{
    BFApplicationArgs::BFApplicationArgs(int argc, char **argv)
    : m_argc(argc)
    , m_argv(argv)
    {
        std::vector<std::string> arguments;
        for(auto i = 1 ; i < argc; ++i)
        {
            const auto str = argv[i];
            arguments.emplace_back(std::string(str));
        }

        BF_PRINT("Command line arguments: {}", Utils::join(arguments, " "));

        for(const auto& arg : arguments)
        {
            std::smatch match;
            std::regex_match(arg, match, std::regex("^([A-Za-z]+)=(.+)$"));

            if(match.empty()) continue;

            std::string key = match.str(1);
            std::string value = match.str(2);

            BF_PRINT("Argument key: {} value: {}", key, value);

            m_arguments.insert({key, value});
        }

        //If base folder is not given, use current directory
        if(m_arguments.find("baseFolder") == m_arguments.end())
        {
            m_arguments.insert({"baseFolder", std::filesystem::current_path().string()});
        }

        //If base folder is empty, use current directory
        else if(std::get<std::string>(m_arguments["baseFolder"]).empty())
        {
            m_arguments["baseFolder"] = std::filesystem::current_path().string();
        }
    }

    int BFApplicationArgs::argc() const
    {
        return m_argc;
    }

    char** const BFApplicationArgs::argv() const
    {
        return m_argv;
    }

    const std::string& BFApplicationArgs::baseFolder() const
    {
        return std::get<std::string>(m_arguments.find("baseFolder")->second);
    }
}