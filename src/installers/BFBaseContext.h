#ifndef BLACKFOX_BASECONTEXT_H
#define BLACKFOX_BASECONTEXT_H

#include "IBFContext.h"
#include "../BFTypeDefs.h"

namespace BlackFox
{
	class BFBaseContext : public IBFContext
	{
	public:
		explicit BFBaseContext(DiContainer container);
		void run() override;
		void addInstaller(DiInstaller installer) override;

	protected:
		DiContainer m_container;
		std::vector<DiInstaller> m_installers;
	};
}

#endif