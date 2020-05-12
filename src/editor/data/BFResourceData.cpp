#include "BFResourceData.h"

namespace BlackFox::Editor
{
	BFResourceData::BFResourceData()
	: Super(Resources::RESOURCE_DATA, "")
	{}

    BFResourceData::BFResourceData(const std::filesystem::path& file)
	: Super(Resources::RESOURCE_DATA, file)
    {}

	BFResourceData::operator std::string() const
	{
		return fmt::format("===Resource Data===\ntype: {}", std::to_string(type.value()));
	}
}

namespace YAML
{
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFResourceData& data)
	{
		out << BeginMap;
		out << Key << "type" << Value << data.type;
		out << EndMap;
		
		return out;
	}
}