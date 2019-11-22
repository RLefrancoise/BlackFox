#ifndef BLACKFOX_IINSTALLER_H
#define BLACKFOX_IINSTALLER_H

#include <memory>

namespace BlackFox
{
	class IBFInstaller
	{
	public:
		virtual ~IBFInstaller() noexcept = default;
		virtual void installBindings(void) = 0;
	};

	typedef std::shared_ptr<IBFInstaller> DiInstaller;
}

#endif