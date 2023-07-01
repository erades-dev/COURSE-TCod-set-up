#ifndef MAP_HPP
#define MAP_HPP

#include "Position.hpp"
#include "Rectangle.hpp"
#include "Tile.hpp"

#include <libtcod/console.hpp>

#include <memory>
#include <vector>

namespace tutorial
{
	class Map {
	public:
		explicit Map(Rectangle size);

		TCODConsole *GetConsole() const {
			return console_.get();
		}

		bool IsWall(Position pos) const;

	private:
		void SetWall(Position pos);

		void Render() const;

		std::vector<Tile> tiles_;
		std::unique_ptr<TCODConsole> console_;

		Rectangle size_;
	};
} // namespace tutorial

#endif // MAP_HPP
