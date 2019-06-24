#ifndef BOARD_GUARD
#define BOARD_GUARD

#include <array>
#include <iostream>
#include <vector>
#include "piece.h"
#include "move.h"

class Board {
 public:
	// Constructor creates chess board with starting pieces
	Board();

	// Create board given board array, next move and check
	Board(std::array<std::array<char, 8>, 8>, char, bool);

	// Cout board like a grid
	friend std::ostream& operator<< (std::ostream& out, const Board& obj);

	// Move piece
	void move_piece(const Move&);

	// Assessors
	char get_next_move() { return next_move; }
	bool board_is_check() { return check; }
	bool board_is_checkmate() { return checkmate; }
	std::vector<Piece> get_black_pieces() { return black_pieces; }
	std::vector<Piece> get_white_pieces() { return white_pieces; }
	std::vector<Move>  get_legal_moves()  { return legal_moves;  }

 private:
	std::array<std::array<char, 8>, 8> board;
	char next_move;
	std::vector<Move> legal_moves;
	bool check;
	bool checkmate;

	void get_pieces_from_board(std::vector<Piece>&, std::vector<Piece>&);
	std::vector<Piece> black_pieces;
	std::vector<Piece> white_pieces;

	void parse_legal_moves();
	void walk_board(std::vector<Move>&, const Piece&, int, int, int);
};

bool is_check(const std::vector<Piece>&, const std::vector<Move>&);
bool piece_is_king(const Piece&);
bool is_checkmate(const std::array<std::array<char, 8>, 8>&, char, bool, std::vector<Move>&);
#endif
