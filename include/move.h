#ifndef MOVE_GUARD
#define MOVE_GUARD

struct Move {
	int from_x, from_y, to_x, to_y;
	bool capture;
	char piece;
  Move(int, int, int, int, bool, char);
	// TODO add function to get notation of move https://en.wikipedia.org/wiki/Chess_notation
};

bool operator== (const Move&, const Move&);
#endif
