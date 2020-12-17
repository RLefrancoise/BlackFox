#include "BFComponentSystemEnums.h"
#include "BFDebug.h"

namespace BlackFox
{
    std::string toString(const ComponentSystemGroups& group)
    {
        switch(group)
        {
            case ComponentSystemGroups ::GameLoop:
                return "GameLoop";
            case ComponentSystemGroups ::EndOfFrame:
                return "EndOfFrame";
            case ComponentSystemGroups ::Render:
                return "Render";
            case ComponentSystemGroups ::FixedTime:
                return "FixedTime";
            case ComponentSystemGroups ::Unknown:
                return "Unknown";
            default:
                BF_EXCEPTION("Unknown group value {}", (int) group);
                break;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const BlackFox::ComponentSystemGroups& group)
{
    using namespace BlackFox;

    stream << toString(group);
    return stream;
}