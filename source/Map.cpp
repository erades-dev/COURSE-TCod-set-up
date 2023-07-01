#include "Map.hpp"

#include "Colors.hpp"
#include "Position.hpp"
#include "Rectangle.hpp"

#include <memory>

namespace tutorial
{
	namespace
	{
		constexpr Position indexToPos(int i, int width) {
			const int y = i / width;
			const int x = i - y * width;

			return Position{x, y};
		}
		constexpr std::size_t posToIndex(Position pos, int width) {
			return (pos.x + pos.y * width);
		}
	} // namespace

	Map::Map(Rectangle size)
		: tiles_(size.width * size.height, Tile{false}),
		  console_(std::make_unique<TCODConsole>(size.width, size.height)),
		  size_(size) {
		this->SetWall({32, 32});
		this->SetWall({33, 32});
		this->Render();
	}

	bool Map::IsWall(Position pos) const {
		const auto index = posToIndex(pos, size_.width);
		return (tiles_.at(index).blocker);
	}

	void Map::SetWall(Position pos) {
		const auto index = posToIndex(pos, size_.width);
		tiles_.at(index).blocker = true;
	}

	void Map::Render() const {
		for (std::size_t i = 0; i < tiles_.size(); ++i) {
			const auto pos = indexToPos(i, size_.width);
			TCODColor color{0, 0, 0};
			if (tiles_[i].blocker) {
				color = color::DarkAzure;
			} else {
				color = color::LightAzure;
			}
			console_->setCharBackground(pos.x, pos.y, color);
		}
	}
} // namespace tutorial
