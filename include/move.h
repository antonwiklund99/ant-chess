#ifndef MOVE_GUARD
#define MOVE_GUARD

#include <string>

struct Move {
	int from_x, from_y, to_x, to_y;
	bool capture;
	char piece;

	// Construct move from long algebraic chess notation
	Move(std::string, char);
  Move(int, int, int, int, bool, char);
	// TODO add function to get notation of move https://en.wikipedia.org/wiki/Chess_notation
};

bool operator== (const Move&, const Move&);
int letter_to_index(char);
#endif
