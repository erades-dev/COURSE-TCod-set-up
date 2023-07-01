#include "Engine.hpp"

#include "Colors.hpp"
#include "Rectangle.hpp"

// #include <libtcod/console.hpp>
// #include <libtcod/sys.hpp>
#include <SDL.h>
#include <libtcod.hpp>

#include <algorithm>
#include <string_view>

namespace tutorial
{
	namespace
	{
		constexpr int window_width = 80;
		constexpr int window_height = 50;
		constexpr std::string_view window_title = "libtcod C++ tutorial 2";
	} // namespace

	Engine::Engine()
		: map_(Rectangle{window_width, window_height}), running_(true) {
		TCODConsole::initRoot(window_width, window_height, window_title.data());

		// console_ = tcod::Console{window_width, window_height};
		// auto params = TCOD_ContextParams{};
		// params.tcod_version = TCOD_COMPILEDVERSION; // This is required.
		// params.console = console_.get();			// Derive the window size from the console size.
		// params.window_title = "Libtcod Project";
		// params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
		// params.vsync = true;
		// auto context = tcod::Context(params);

		next_event_ = Event::None;
		entities_.emplace_back(Position{window_width / 2, window_height / 2}, color::White);
		entities_.emplace_back(Position{63, 10}, color::Yellow);
		player_ = &(entities_[0]);
	}

	Engine::~Engine() {
		TCOD_quit();
	}

	void Engine::Input() {
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr, false);

		Event event = Event::None;
		switch (key.vk) {
		case TCODK_UP:
			event = Event::MoveUp;
			break;
		case TCODK_DOWN:
			event = Event::MoveDown;
			break;
		case TCODK_LEFT:
			event = Event::MoveLeft;
			break;
		case TCODK_RIGHT:
			event = Event::MoveRight;
			break;
		case TCODK_ESCAPE:
			event = Event::Quit;
			break;
		default:
			break;
		}
		next_event_ = event;
	}

	void Engine::Update() {
		if (next_event_ == Event::None) {
			return;
		}
		if (next_event_ == Event::Quit) {
			Quit();
			return;
		}

		auto pos = player_->GetPos();
		switch (next_event_) {
		case Event::MoveUp:
			--pos.y;
			break;
		case Event::MoveDown:
			++pos.y;
			break;
		case Event::MoveLeft:
			--pos.x;
			break;
		case Event::MoveRight:
			++pos.x;
			break;
		default:
			break;
		}

		if (this->CanMove(pos)) {
			player_->SetPos(pos);
		}
		next_event_ = Event::None;
	}

	bool Engine::IsRunning() const {
		return (running_ && !TCODConsole::isWindowClosed());
	}

	void Engine::Render() const {
		TCODConsole::root->clear();
		this->RenderMap();
		this->RenderEntities();
		TCODConsole::root->flush();
	}

	void Engine::Quit() {
		running_ = false;
	}

	bool Engine::CanMove(Position pos) const {
		if (!IsInBounds(pos)) {
			return false;
		}
		if (map_.IsWall(pos)) {
			return false;
		}
		for (auto entity : entities_) {
			if (pos == entity.GetPos()) {
				return false;
			}
		}
		return true;
	}

	bool Engine::IsInBounds(Position pos) const {
		const auto width = TCODConsole::root->getWidth();
		const auto height = TCODConsole::root->getHeight();
		return (pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height);
	}

	void Engine::RenderEntities() const {
		// Show the position of each entity
		std::for_each(entities_.cbegin(), entities_.cend(), [](const auto entity) {
			constexpr char icon = '@';

			const auto pos = entity.GetPos();
			TCODConsole::root->putChar(pos.x, pos.y, icon);

			const auto color = entity.GetColor();
			TCODConsole::root->setCharForeground(pos.x, pos.y, color);
		});
	}

	void Engine::RenderMap() const {
		const auto *console = map_.GetConsole();
		TCODConsole::root->blit(console, 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, 0, 0);
	}
} // namespace tutorial

// tcod::Console console = tcod::Console{window_width, window_height};
// auto params = TCOD_ContextParams{};
// params.tcod_version = TCOD_COMPILEDVERSION;
// params.console = console.get();
// params.window_title = "Libtcod Project";
// params.vsync = true;
///* auto tileset = tcod::load_tilesheet("terminal8x8_gs_ro.png", {16, 16}, tcod::CHARMAP_CP437);
// params.tileset = tileset.get();*/
// tcod::Context context = tcod::Context(params);
