#include "BFApplicationArgs.h"
#include "BFStringUtils.h"
#include "BFDebug.h"

#include <regex>
#include <vector>
#include <filesystem>

namespace BlackFox
{
    BFApplicationArgs::BFApplicationArgs(int argc, char **argv)
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

            if(key == "baseFolder")
                baseFolder = value;
        }

        //If base folder is empty, use current directory
        if(baseFolder == "")
        {
            baseFolder = std::filesystem::current_path().string();
        }
    }
}