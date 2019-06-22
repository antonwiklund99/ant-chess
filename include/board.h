#ifndef BOARD_GUARD
#define BOARD_GUARD

#include <iostream>
#include <vector>
#include "piece.h"
#include "move.h"

class Board {
 public:
	Board();
	// Cout board like a grid
	friend std::ostream& operator<< (std::ostream& out, const Board& obj);

	// Move piece
	void move_piece(const Move&);

	// Assessors
	char get_next_move() { return next_move; }
	std::vector<Piece> get_black_pieces() { return black_pieces; }
	std::vector<Piece> get_white_pieces() { return white_pieces; }
	std::vector<Move>  get_legal_moves()  { return legal_moves;  }

 private:
	char board [8][8];
	char next_move;
	std::vector<Move> legal_moves;

	void get_pieces_from_board(std::vector<Piece>&, std::vector<Piece>&);
	std::vector<Piece> black_pieces;
	std::vector<Piece> white_pieces;

	void parse_legal_moves();
	void walk_board(std::vector<Move>&, const Piece&, int, int, int);
};

#endif
