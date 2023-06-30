#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Event.hpp"
#include "Position.hpp"

namespace tutorial {
class Engine {
public:
	Engine();
	~Engine();

	void HandleInput();
	void Update();

	bool IsRunning() const;
	void Render() const;

private:
	void Quit();

	Position player_pos_;
	Event next_event_;
	bool running_;
};
} // namespace tutorial

#endif // ENGINE_HPP