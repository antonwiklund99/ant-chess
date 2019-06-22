#include "piece.h"
#include <cctype>

Piece::Piece(char c, int f, int e) {
	symbol = c;
	y = f;
	x = e;
	if (isupper(symbol)) {
		color = 'b';
	}
	else {
		color = 'w';
	}
}

bool operator== (const Piece& lhs, const Piece& rhs) {
	return (lhs.symbol == rhs.symbol && lhs.y == rhs.y && lhs.x == rhs.x);
}
