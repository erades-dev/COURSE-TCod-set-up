

#include <libtcod.hpp>
// #include <libtcod/console.hpp>
// #include <libtcod/sys.hpp>

#include "Engine.hpp"
#include "Event.hpp"
#include "Position.hpp"

// #include <string_view>

namespace tutorial {
Engine::Engine()
	: running_(true) {
	constexpr int window_width = 80;
	constexpr int window_height = 50;

	// tcod::Console console = tcod::Console{window_width, window_height};
	// auto params = TCOD_ContextParams{};
	// params.tcod_version = TCOD_COMPILEDVERSION;
	// params.console = console.get();
	// params.window_title = "Libtcod Project";
	// params.vsync = true;
	///* auto tileset = tcod::load_tilesheet("terminal8x8_gs_ro.png", {16, 16}, tcod::CHARMAP_CP437);
	// params.tileset = tileset.get();*/
	// tcod::Context context = tcod::Context(params);

	TCODConsole::initRoot(window_width, window_height, "libtcod C++ tutorial");
	player_pos_ = Position{window_width / 2, window_height / 2};
}

Engine::~Engine() {
	TCOD_quit();
}

void Engine::HandleInput() {
	TCOD_key_t key{};													  // create a key object
	TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr, false); // wait for user to press a key

	switch (key.vk) {
	case TCODK_UP:
		next_event_ = Event::MoveUp;
		break;
	case TCODK_DOWN:
		next_event_ = Event::MoveDown;
		break;
	case TCODK_LEFT:
		next_event_ = Event::MoveLeft;
		break;
	case TCODK_RIGHT:
		next_event_ = Event::MoveRight;
		break;
	case TCODK_ESCAPE:
		next_event_ = Event::Quit;
		break;
	default:
		next_event_ = Event::None;
		break;
	}
}

void Engine::Update() {
	switch (next_event_) {
	case Event::MoveUp:
		--player_pos_.y;
		break;
	case Event::MoveDown:
		++player_pos_.y;
		break;
	case Event::MoveLeft:
		--player_pos_.x;
		break;
	case Event::MoveRight:
		++player_pos_.x;
		break;
	case Event::Quit:
		Quit();
		break;
	default:
		break;
	}
}

bool Engine::IsRunning() const {
	return running_;
}

void Engine::Render() const {
	TCODConsole::root->clear();									   // Clear the console before we render anything
	TCODConsole::root->putChar(player_pos_.x, player_pos_.y, '@'); // Render an @ at the player position
	TCODConsole::root->flush();									   // Flushing the console redraws it to the screen
}

void Engine::Quit() {
	running_ = false;
}
} // namespace tutorial
