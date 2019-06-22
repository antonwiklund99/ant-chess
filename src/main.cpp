#include "board.h"
#include "piece.h"
#include <iostream>
#include <vector>
using std::vector;
int main(int argc, char *argv[]) {
	Board board;
	std::cout << board;
	vector<Piece> bp = board.get_black_pieces();
	vector<Piece> wp = board.get_white_pieces();
	for (auto it = bp.begin(); it != bp.end(); ++it) {
		std::cout << it->symbol << " " << it->y << " " << it->x << "\n";
	}
	std::cout << "\n";
	for (auto it = wp.begin(); it != wp.end(); ++it) {
		std::cout << it->symbol << " " << it->y << " " << it->x << "\n";
	}
	return 0;
}
