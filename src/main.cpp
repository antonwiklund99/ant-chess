
#include "board.h"
#include "piece.h"
#include "move.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	Board board;
	cout << board;
	/*
	vector<Piece> bp = board.get_black_pieces();
	vector<Piece> wp = board.get_white_pieces();
	for (auto it = bp.begin(); it != bp.end(); ++it) {
		cout << it->symbol << " " << it->y << " " << it->x << "\n";
	}
	cout << "\n";
	for (auto it = wp.begin(); it != wp.end(); ++it) {
		cout << it->symbol << " " << it->y << " " << it->x << "\n";
		}*/
	std::string m;
	do {
		cout << "[Piece cordinate from(xy)][x/-][cordinate to]" << endl;
		std::cin >> m;

		Move t(m, board.get_next_move());
		try {
			board.move_piece(t);
		}
		catch(std::invalid_argument) {
			cout << "invalid argument" << endl;
		}

		auto moves = board.get_legal_moves();
		cout << "legal moves:" << endl;
		for (auto it = moves.begin(); it != moves.end(); ++it) { /*
			cout << "From:" << it->from_x << " " << it->from_y << " " <<
			it->to_x << " " << it->to_y << " Piece: " << it->piece << '\n';*/
			cout << (*it).notation() << endl;
		}
		cout << "next move = " << board.get_next_move() << "\n";
		cout << "check = " << board.board_is_check() << '\n';
		cout << "checkmate = " << board.board_is_checkmate() << '\n';
		cout << board << "\n";
	} while(!board.board_is_checkmate());
	return 0;
}
