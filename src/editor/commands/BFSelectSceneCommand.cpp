#include "BFSelectSceneCommand.h"
#include "BFDebug.h"

namespace BlackFox::Editor
{
	BFSelectSceneCommand::BFSelectSceneCommand()
		: m_scene {0}
	{
	}

	void BFSelectSceneCommand::setScene(const int scene)
	{
		m_scene = scene;
	}

	void BFSelectSceneCommand::execute()
	{
		print("Select scene {}", m_scene);
	}

	BFSelectSceneCommand* BFSelectSceneCommand::clone() const
	{
		return new BFSelectSceneCommand();
	}
}
