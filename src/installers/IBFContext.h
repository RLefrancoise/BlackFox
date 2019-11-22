#ifndef BLACKFOX_ICONTEXT_H
#define BLACKFOX_ICONTEXT_H

#include "IBFInstaller.h"

namespace BlackFox
{
	class IBFContext
	{
	public:
		virtual ~IBFContext() noexcept = default;
		virtual void run() = 0;
		virtual void addInstaller(DiInstaller installer) = 0;
	};

	typedef std::shared_ptr<IBFContext> DiContext;
}

#endif