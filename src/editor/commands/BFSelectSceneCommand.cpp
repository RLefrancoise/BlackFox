#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	void BFSelectSceneCommand::execute(const int scene)
	{
		print("Select scene {}", scene);
	}

	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand();
	}
}
