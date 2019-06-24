#include "board.h"
#include "piece.h"
#include "move.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <array>
using std::array;
using std::isupper;
using std::islower;
using std::ostream;
using std::vector;
using std::tolower;
using std::find;
using std::find_if;

// Constructor for Board class, creates starting board, puts pieces into vectors
// and set next move to white
Board::Board() : board {{
												{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
												{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
												{'0', '0', '0', '0', '0', '0', '0', '0'},
												{'0', '0', '0', '0', '0', '0', '0', '0'},
												{'0', '0', '0', '0', '0', '0', '0', '0'},
												{'0', '0', '0', '0', '0', '0', '0', '0'},
												{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
												{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
												 }}, next_move('w'), check(false), checkmate(false) {
	get_pieces_from_board(black_pieces, white_pieces);
	parse_legal_moves();
}

// Constructor for board give all member variables
Board::Board(array<array<char, 8>, 8> b, char nm, bool c ) :
	board(b), next_move(nm), check(c) {
	get_pieces_from_board(black_pieces, white_pieces);
	parse_legal_moves();
}

// Parses board and puts pieces into two vectors
void Board::get_pieces_from_board(vector<Piece>& black, vector<Piece>& white) {
	black.clear();
	white.clear();
	for (int i =  0; i != 8; ++i) {
		for (int n = 0; n != 8; ++n) {
			if (board[i][n] != '0') {
				Piece p(board[i][n], i, n);
				if (isupper(board[i][n])) {
					black.push_back(p);
				}
				else {
					white.push_back(p);
				}
			}
		}
	}
}

void Board::parse_legal_moves() {
	legal_moves.clear();
	const vector<Piece> &piece_vector = (next_move == 'w') ? white_pieces : black_pieces;

	for (auto it = piece_vector.begin(); it != piece_vector.end(); ++it) {
		switch(tolower(it->symbol)) {
		case 'r':
			walk_board(legal_moves, *it, 1, 0, 8);
			walk_board(legal_moves, *it, -1, 0, 8);
			walk_board(legal_moves, *it, 0, 1, 8);
			walk_board(legal_moves, *it, 0, -1, 8);
			break;
		case 'n':
			walk_board(legal_moves, *it, 2, 1, 1);
			walk_board(legal_moves, *it, 2, -1, 1);
			walk_board(legal_moves, *it, -2, 1, 1);
			walk_board(legal_moves, *it, -2, -1, 1);
			walk_board(legal_moves, *it, 1, 2, 1);
			walk_board(legal_moves, *it, -1, 2, 1);
			walk_board(legal_moves, *it, 1, -2, 1);
			walk_board(legal_moves, *it, -1, 2, 1);
			break;
		case 'b':
			walk_board(legal_moves, *it, 1, 1, 8);
			walk_board(legal_moves, *it, 1, -1, 8);
			walk_board(legal_moves, *it, -1, 1, 8);
			walk_board(legal_moves, *it, -1, -1, 8);
			break;
		case 'q':
			walk_board(legal_moves, *it, 1, 1, 8);
			walk_board(legal_moves, *it, 1, -1, 8);
			walk_board(legal_moves, *it, -1, 1, 8);
			walk_board(legal_moves, *it, -1, -1, 8);
			walk_board(legal_moves, *it, 1, 0, 8);
			walk_board(legal_moves, *it, -1, 0, 8);
			walk_board(legal_moves, *it, 0, 1, 8);
			walk_board(legal_moves, *it, 0, -1, 8);
			break;
		case 'k':
			walk_board(legal_moves, *it, 1, 1, 1);
			walk_board(legal_moves, *it, 1, -1, 1);
			walk_board(legal_moves, *it, -1, 1, 1);
			walk_board(legal_moves, *it, -1, -1, 1);
			walk_board(legal_moves, *it, 1, 0, 1);
			walk_board(legal_moves, *it, -1, 0, 1);
			walk_board(legal_moves, *it, 0, 1, 1);
			walk_board(legal_moves, *it, 0, -1, 1);
			break;
		case 'p':
			if (it->color == 'w') {
				// If pawn is on its original place it can move 2 tiles
				if (it->y == 6) {
					walk_board(legal_moves, *it, -1, 0, 2);
				}
				else {
					walk_board(legal_moves, *it, -1, 0, 1);
				}
				// Check for capture
				if (board[it->y - 1][it->x - 1] != '0' && isupper(board[it->y - 1][it->x - 1])) {
					Move m(it->x, it->y, it->x - 1, it->y - 1, true, it->symbol);
					legal_moves.push_back(m);
				}
				else if (board[it->y - 1][it->x + 1] != '0' && isupper(board[it->y - 1][it->x + 1])) {
					Move m(it->x, it->y, it->x + 1, it->y - 1, true, it->symbol);
					legal_moves.push_back(m);
				}
			}
			else {
				if (it->y == 1) {
				  walk_board(legal_moves, *it, 1, 0, 2);
				}
				else {
					walk_board(legal_moves, *it, 1, 0, 1);
				}
				if (board[it->y + 1][it->x - 1] != '0' && islower(board[it->y + 1][it->x - 1])) {
					Move m(it->x, it->y, it->x - 1, it->y + 1, true, it->symbol);
					legal_moves.push_back(m);
				}
				else if (board[it->y - 1][it->x + 1] != '0' && islower(board[it->y + 1][it->x + 1])) {
					Move m(it->x, it->y, it->x + 1, it->y + 1, true, it->symbol);
					legal_moves.push_back(m);
				}
			}
			break;
		default:
			throw std::domain_error("Unknown piece symbol");
		}
	}
}

// Walks the board in direction til it finds other piece or end of board, inserts each legal
// move into referenced vector
void Board::walk_board(vector<Move>& move_vec, const Piece& p, int y_dir, int x_dir, int cap) {
	int new_xpos, new_ypos;
	for (int n = 1; n != cap + 1; ++n) {
		new_ypos = p.y + y_dir * n;
		new_xpos = p.x + x_dir * n;
		// Check if new pos legal_movesside board
		if (new_ypos > 7 || new_ypos < 0 || new_xpos > 7 || new_xpos < 0){
			return;
		}
		// If move is on empty space, add move to vector
		else if (board[new_ypos][new_xpos] == '0') {
			Move m(p.x, p.y, new_xpos, new_ypos, false, p.symbol);
			move_vec.push_back(m);
		}
		// Move is on piece
		else {
			if ((islower(board[new_ypos][new_xpos]) && islower(p.symbol)) ||
					(isupper(board[new_ypos][new_xpos]) && isupper(p.symbol)) ||
					tolower(p.symbol) == 'p') {
				// Position is on piece with same color or piece is pawn and cant capture
				return;
			}
			else {
				Move m(p.x, p.y, new_xpos, new_ypos, true, p.symbol);
				move_vec.push_back(m);
				return;
			}
		}
	}
}

// Do Move m
void Board::move_piece(const Move& m) {
	// Check if move is legal
	if (!(find(legal_moves.begin(), legal_moves.end(), m) != legal_moves.end())) {
		throw std::invalid_argument("Move is not a legal move");
	}

	// Set check to false because it can longer be it if move is legal
	check = false;

	vector<Piece>& target_vec = (next_move != 'w') ? white_pieces : black_pieces;
	if (m.capture) {
		// Removes captured piece from pieces vector
		Piece target(board[m.to_y][m.to_x], m.to_y, m.to_x);
		auto remove_target = find(target_vec.begin(), target_vec.end(), target);
		target_vec.erase(remove_target);
	}

	// Change x,y cords in vector
	vector<Piece>& piece_vec = (next_move == 'w') ? white_pieces : black_pieces;
	for (auto it = piece_vec.begin(); it != piece_vec.end(); ++it) {
		if (it->y == m.from_y && it->x == m.from_x) {
			it->y = m.to_y;
			it->x = m.to_x;
			break;
		}
	}

	// Check if move puts board other side in check
	parse_legal_moves();
	check = is_check(target_vec, legal_moves);

	// Move piece on board
	board[m.to_y][m.to_x] = board[m.from_y][m.from_x];
	board[m.from_y][m.from_x] = '0';

	// Change turn
	next_move = (next_move == 'w') ? 'b' : 'w';

	// Generate new legal moves list
	parse_legal_moves();
	if (check) {
		// Check for checkmate
		auto fml = legal_moves;
		checkmate = is_checkmate(board, next_move, check, fml);
		legal_moves = fml;
	}
}

bool is_check(const vector<Piece>& target_vec, const vector<Move>& move_vec) {
	// Check for check TODO: maybe make a seperate variable for king postion
	auto king_piece = find_if(target_vec.begin(), target_vec.end(), piece_is_king);
	for (auto it = move_vec.begin(); it != move_vec.end(); ++it) {
		if (it->to_x == king_piece->x && it->to_y == king_piece->y) {
			return true;
		}
	}
	return false;
}

bool piece_is_king(const Piece& p) {
	return (tolower(p.symbol) == 'k');
}

bool is_checkmate(const array<array<char, 8>, 8>& b, char nm, bool c, vector<Move>& leg_moves) {
	// TODO fix this, if other side also has check sketchy stuff will happen
	for (auto it = leg_moves.begin(); it != leg_moves.end();) {
		Board tmp_board(b, nm, c);
		tmp_board.move_piece(*it);
		if (is_check(tmp_board.get_next_move() == 'w' ? tmp_board.get_black_pieces() :
								 tmp_board.get_white_pieces(), tmp_board.get_legal_moves())){
			it = leg_moves.erase(it);
		}
		else {
			++it;
		}
	}
	if (leg_moves.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

// When printing board class print board array
ostream& operator<< (ostream& out, const Board& obj) {
	for (int i = 0; i != 8; ++i) {
    for (int n = 0; n != 8; ++n) {
			out << obj.board[i][n] << " ";
		}
		out << "\n";
	}
	return out;
}
