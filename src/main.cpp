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
	std::array<std::array<char, 8>, 8> checkmatedBoard = {{
																												 {'0','0','0','0','0','K','0','0'},
																												 {'R','0','0','0','0','P','0','0'},
																												 {'0','0','0','0','0','q','0','P'},
																												 {'P','0','0','0','0','P','0','0'},
																												 {'p','B','n','Q','0','0','0','0'},
																												 {'0','p','0','0','0','r','0','0'},
																												 {'0','0','0','0','0','p','k','p'},
																												 {'0','0','0','0','0','0','0','0'}
																												 }};
	Board board(checkmatedBoard, 'b');
	cout << board;
	auto moves = board.get_legal_moves();
	for (auto it = moves.begin(); it != moves.end(); ++it) {
		cout << (*it).notation() << endl;
	}
	std::string m;
	while(!board.board_is_checkmate()) {
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
		for (auto it = moves.begin(); it != moves.end(); ++it) {
			cout << (*it).notation() << endl;
		}
		cout << "next move = " << board.get_next_move() << "\n";
		cout << "check = " << board.board_is_check() << '\n';
		cout << "checkmate = " << board.board_is_checkmate() << '\n';
		cout << board << "\n";
	}
	cout << "Checkmate, " << board.get_next_move() << " lost" << endl;
	return 0;
}
