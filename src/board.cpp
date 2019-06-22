#include "board.h"
#include "piece.h"
#include <iostream>
#include <vector>
#include <cctype>
using std::isupper;
using std::ostream;
using std::vector;

// Constructor for Board class, creates starting board, puts pieces into vectors
// and set next move to white
Board::Board() : board {
												'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
												'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
												'0', '0', '0', '0', '0', '0', '0', '0',
												'0', '0', '0', '0', '0', '0', '0', '0',
												'0', '0', '0', '0', '0', '0', '0', '0',
												'0', '0', '0', '0', '0', '0', '0', '0',
												'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
												'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'
}, next_move('w') {
	get_pieces_from_board(black_pieces, white_pieces);
}

//vector<>https://en.wikipedia.org/wiki/Algebraic_notation_(chess)

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
