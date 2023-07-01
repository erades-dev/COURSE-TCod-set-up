#include "Engine.hpp"

int main(int argc, char* argv[]) {
	// Initialize the engine, which will create the tcod window
	tutorial::Engine engine{};

	while (engine.IsRunning()) {
		engine.Render();	  // render everything to the screen
		engine.Input(); // get input from user
		engine.Update();	  // do any game updates
	}

	return 0;
}

// #include <iostream>
// #include <SDL.h>
// #include <libtcod.hpp>
//
// int main(int argc, char *argv[]) {
//	tcod::Console console = tcod::Console{80, 25}; // Main console.
//	auto params = TCOD_ContextParams{};
//	params.tcod_version = TCOD_COMPILEDVERSION; // This is required.
//	params.console = console.get();				// Derive the window size from the console size.
//	params.window_title = "Libtcod Project";
//	params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
//	params.vsync = true;
//	params.argc = argc; // This allows some user-control of the context.
//	params.argv = argv;
//	/* auto tileset = tcod::load_tilesheet("terminal8x8_gs_ro.png", {16, 16}, tcod::CHARMAP_CP437);
//	 params.tileset = tileset.get();*/
//	tcod::Context context = tcod::Context(params);
//
//	int playerx = 6, playery = 6;
//	while (1) {
//		SDL_Event event;
//		TCOD_console_clear(console.get());
//		// tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
//		tcod::print(console, {playerx, playery}, "@", std::nullopt, std::nullopt);
//		context.present(console); // Updates the visible display.
//
//		SDL_WaitEvent(nullptr); // Optional, sleep until events are available.
//		while (SDL_PollEvent(&event)) {
//			// context.convert_event_coordinates(event); // Optional, converts pixel coordinates into tile coordinates.
//			switch (event.type) {
//			case SDL_KEYUP:
//				if (event.key.keysym.sym == SDLK_UP)
//					playery--;
//				if (event.key.keysym.sym == SDLK_DOWN)
//					playery++;
//				if (event.key.keysym.sym == SDLK_LEFT)
//					playerx--;
//				if (event.key.keysym.sym == SDLK_RIGHT)
//					playerx++;
//				break;
//			case SDL_QUIT:
//				return (0); // Exit.
//			}
//		}
//	}
// }

// #include <libtcod.hpp>
// #include <SDL.h>
// #include <libtcod.hpp>
//
// int main(int argc, char *argv[]) {
//	int playerx = 40, playery = 25;
//	TCODConsole::initRoot(80, 50, "libtcod C++ tutorial", false);
//	while (!TCODConsole::isWindowClosed()) {
//		TCOD_key_t key;
//		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
//		switch (key.vk) {
//		case TCODK_UP: playery--; break;
//		case TCODK_DOWN: playery++; break;
//		case TCODK_LEFT: playerx--; break;
//		case TCODK_RIGHT: playerx++; break;
//		default: break;
//		}
//		TCODConsole::root->clear();
//		TCODConsole::root->putChar(playerx, playery, '@');
//		TCODConsole::flush();
//	}
//	return 0;
//}
