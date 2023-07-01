#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <libtcod.hpp>
#include <vector>
#include "Event.hpp"
#include "Position.hpp"
#include "Entity.hpp"
#include "Map.hpp"

namespace tutorial
{
	class Engine {
	public:
		Engine();
		~Engine();

		void Input();
		void Update();

		bool IsRunning() const;
		void Render() const;

	private:
		void Quit();

		bool CanMove(Position pos) const;
		bool IsInBounds(Position pos) const;
		void RenderEntities() const;
		void RenderMap() const;

		tcod::Context context_;
		tcod::Console console_;
		Map map_;
		std::vector<Entity> entities_;
		Entity *player_;
		Event next_event_;
		bool running_;
	};
} // namespace tutorial

#endif // ENGINE_HPP