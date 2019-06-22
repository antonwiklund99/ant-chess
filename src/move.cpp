#include "move.h"
Move::Move(int fx, int fy, int tx, int ty, bool x, char p):
		from_x(fx), from_y(fy), to_x(tx), to_y(ty), capture(x), piece(p) {}

bool operator== (const Move& lhs, const Move& rhs) {
	return (lhs.from_x == rhs.from_x && lhs.to_x == rhs.to_x && lhs.from_y == rhs.from_y &&
					lhs.to_y == rhs.to_y && lhs.piece == rhs.piece && lhs.capture == rhs.capture);
}
