#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	void BFSelectSceneCommand::execute(const int scene)
	{
		BF_PRINT("Select scene {}", scene);
	}

	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand();
	}
}
