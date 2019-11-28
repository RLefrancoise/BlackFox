#include "BFBaseInstaller.h"

namespace BlackFox
{
	BFBaseInstaller::BFBaseInstaller(DiContainer container)
	: m_container(std::move(container))
	{
	}
}