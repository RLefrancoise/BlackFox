#include "core/BFApplication.h"

using namespace BlackFox;

int main(int argc, char** argv)
{
	sdl::Root root;
	sdl::Window window("Black Fox", sdl::Vec2i(800, 600), SDL_INIT_EVENTS);
	BFApplication app(root, window);
	return app.execute();
}

