#include <iostream>
#include "core/BFApplication.h"

using namespace BlackFox;

int main(int argc, char** argv)
{
	//Get the app
	auto& app = BFSingleton<BFApplication>::get();
	//Execute the app
	return app.execute();
}