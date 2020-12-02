#include "boot/BFBootstrap.h"
#include "TestGame.h"

using namespace BlackFox;

int main(int argc, char** argv)
{
	BFBootstrap boot;
	return boot.run<TestExample::TestGame>(argc, argv);
}