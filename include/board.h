#ifndef BOARD_GUARD
#define BOARD_GUARD

#include <iostream>
#include <vector>
#include "piece.h"

class Board {
 public:
	Board();
	friend std::ostream& operator<< (std::ostream& out, const Board& obj);

	// Assessors
	char get_next_move() { return next_move; }
	std::vector<Piece> get_black_pieces() { return black_pieces; }
	std::vector<Piece> get_white_pieces() { return white_pieces; }

 private:
	char board [8][8];
	char next_move;
	void get_pieces_from_board(std::vector<Piece>&, std::vector<Piece>&);
	std::vector<Piece> black_pieces;
	std::vector<Piece> white_pieces;
};
#endif
