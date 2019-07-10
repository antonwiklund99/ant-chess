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

	// Create board given board array and next move
	Board(std::array<std::array<char, 8>, 8>, char);

	// Cout board like a grid
	friend std::ostream& operator<< (std::ostream& out, const Board& obj);

	friend void clean_checked_moves(const std::array<std::array<char, 8>, 8>&, char,
																	std::vector<Move>&);

	// Move piece
	void move_piece(const Move& m) { move_piece(m, true); }
	void move_piece(const Move&, bool);

	// Assessors
	char get_next_move() { return next_move; }
	bool board_is_check() { return check; }
	bool board_is_checkmate() { return checkmate; }
	std::vector<Piece> get_black_pieces() { return black_pieces; }
	std::vector<Piece> get_white_pieces() { return white_pieces; }
	std::vector<Move>  get_legal_moves()  { return legal_moves;  }

 private:
	// Constructor only used by clean_checked_moves
	Board(std::array<std::array<char, 8>, 8>, char, bool);

	std::array<std::array<char, 8>, 8> board;
	char next_move;
	std::vector<Move> legal_moves;
	bool check;
	bool checkmate;

	void get_pieces_from_board(std::vector<Piece>&, std::vector<Piece>&);
	std::vector<Piece> black_pieces;
	std::vector<Piece> white_pieces;

	void parse_legal_moves(char);
	void walk_pawn(std::vector<Move>&, const Piece&, int);
	void walk_board(std::vector<Move>&, const Piece&, int, int, int);
};

// Args: Piece vector for target (not next_move) team and vector of legal moves
bool is_check(const std::vector<Piece>&, const std::vector<Move>&);
bool piece_is_king(const Piece&);
void clean_checked_moves(const std::array<std::array<char, 8>, 8>&, char, std::vector<Move>&);
#endif
