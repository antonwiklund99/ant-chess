#include "board.h"
#include "piece.h"
#include "move.h"
#include <iostream>
#include <vector>
using std::vector;
int main(int argc, char *argv[]) {
	Board board;
	std::cout << board;
	/*
	vector<Piece> bp = board.get_black_pieces();
	vector<Piece> wp = board.get_white_pieces();
	for (auto it = bp.begin(); it != bp.end(); ++it) {
		std::cout << it->symbol << " " << it->y << " " << it->x << "\n";
	}
	std::cout << "\n";
	for (auto it = wp.begin(); it != wp.end(); ++it) {
		std::cout << it->symbol << " " << it->y << " " << it->x << "\n";
		}*/

	int fy,fx,ty,tx;
	bool c;
	char p;
	for (int i = 0; i != 10; ++i) {
	vector<Move> legal = board.get_legal_moves();
	for (auto it = legal.begin(); it != legal.end(); ++it) {
		std::cout << it->from_x << " " << it->from_y << " "
							<< it-> to_x << " " << it->to_y << " "
			        << it-> capture << " " << it->piece << "\n";}
		std::cout << "From x, from y, to x, to y, capture, piece" << std::endl;
		std::cin >> fx >> fy >> tx >> ty >> c >> p;
		Move m(fx, fy, tx, ty, c, p);
		board.move_piece(m);
		std::cout << board.get_next_move() << "\n";
		std::cout << board << "\n";
	}
	return 0;
}
