#ifndef POSITION_HPP
#define POSITION_HPP

namespace tutorial
{
	struct Position {
		int x;
		int y;
	};

	constexpr bool operator==(Position lhs, Position rhs) {
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}

	constexpr bool operator!=(Position lhs, Position rhs) {
		return !(lhs == rhs);
	}
} // namespace tutorial

#endif // POSITION_HPP