#include "board.h"
#include "piece.h"
#include "move.h"
#include "mcts.h"
#include "graphicshandler.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	Board board;
	std::string m;
	Graphicshandler graphicshandler;
	while(!board.board_is_checkmate() && !board.board_is_stalemate()) {
		graphicshandler.update(board.get_board());
		if (board.get_next_move() == 'w') {
			cout << "next move = " << board.get_next_move() << "\n";
			cout << "check = " << board.board_is_check() << '\n';
			cout << "checkmate = " << board.board_is_checkmate() << '\n';
			cout << "stalemate = " << board.board_is_stalemate() << '\n';
			//		cout << "predicted move = " << computeBestMove(board).notation() << '\n';
			cout << board << "\n";
			auto moves = board.get_legal_moves();
			cout << "legal moves:" << endl;
			for (auto it = moves.begin(); it != moves.end(); ++it) {
				cout << (*it).notation() << endl;
			}

			cout << "[Piece cordinate from(xy)][x/-][cordinate to]" << endl;
			std::cin >> m;
			if (m == "quit") {
				graphicshandler.close();
				return 0;
			}

			try {
				Move t(m, board.get_next_move());
				board.move_piece(t);
			}
			catch(std::invalid_argument) {
				cout << "invalid argument" << endl;
			}
		}
		else {
			Move m = computeBestMove(board);
			board.move_piece(m);
      cout << "Move chosen: " << m.notation() << endl;
		}
	}
	cout << "Checkmate, " << board.get_next_move() << " lost" << endl;
	graphicshandler.close();
	return 0;
}
