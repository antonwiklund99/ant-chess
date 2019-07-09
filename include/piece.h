#ifndef PIECE_GUARD
#define PIECE_GUARD
struct Piece {
	char symbol;
	char color;
	int y;
	int x;
  Piece(char, int, int);
};

bool operator== (const Piece&, const Piece&);
bool operator< (const Piece&, const Piece&);
int pieceValue(char);
#endif
