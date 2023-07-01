#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Position.hpp"
#include <libtcod/color.hpp>

namespace tutorial {
	class Entity {
	public:
		explicit Entity(Position pos, TCODColor color)
			: pos_(pos), color_(color) {
		}

		void SetPos(Position pos) {
			pos_ = pos;
		}

		TCODColor GetColor() const {
			return color_;
		}

		Position GetPos() const {
			return pos_;
		}

	private:
		Position pos_;
		TCODColor color_;
	};
} // namespace tutorial

#endif // ENTITY_HPP
