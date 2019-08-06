#include <math.h>
#include <map>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "move.h"
#include "board.h"
#include "mcts.h"
using std::vector;
using std::map;
using std::string;
using std::pair;
using std::sort;

#define NUMBER_OF_SEARCH_ITERATIONS 1000
#define MAX_SEARCH_DEPTH 100

Node::Node(Node* p) {
	simulations = 0;
	score = 0;
	parent = p;
}

Move computeBestMove(const Board& startBoard) {
	// Create root node
	Tree tree;
	Node *headptr = &tree.root;

	int r, totalMoves, wasWin, wasDraw;
	Board b;
	vector<Move> m;
	string optimalMove;
	srand(time(NULL));
	for (int i = 0; i < NUMBER_OF_SEARCH_ITERATIONS; i++) {
		if (!(i%10)) std::cout << "Search number: " << i << std::endl;
		b = startBoard;
		totalMoves = 0;

		// Break loop on exeding search depth or check/stalemate
		while (true) {
			m = b.get_legal_moves();

			// If no playout from node has been made choose random move
			if (headptr->children.size() == 0) {
				r = rand() % m.size() + 0;
				optimalMove = m[r].notation();
			}
			// If all nodes have had full playouts, run nodes through uct and chose most promising one
			else if (headptr->children.size() == m.size()) {
				if (headptr->children.size() == 1) {
					optimalMove = headptr->children.begin()->first;
				}
				else {
					double bestScore = 0, ret;
					for (auto it = headptr->children.begin(); it != headptr->children.end(); ++it) {
						ret = uct(it->second.score, it->second.simulations, headptr->simulations);
						if (ret > bestScore) {
							bestScore = ret;
							optimalMove = it->first;
							//std::cout << "Move: " << optimalMove << "m.size() = " << m.size() << std::endl;
						}
					}
				}
			}
			// Some nodes have been explored chose first unexplored one
			else {
				auto it = m.begin();
				while(it != m.end()) {
					if (headptr->children.find(it->notation()) == headptr->children.end()) {
						optimalMove = it->notation();
						break;
					}
					it++;
				}
			}
			b.move_piece(Move(optimalMove, b.get_next_move()));

			if (b.board_is_checkmate() || b.board_is_stalemate() || totalMoves > MAX_SEARCH_DEPTH) {
				// Get if end was win or loss
				wasWin = 2*(b.board_is_checkmate() && (b.get_next_move() != startBoard.get_next_move()));
        wasDraw = b.board_is_stalemate();

				// Traverse back through tree untill reaching root node
				while (headptr != &tree.root) {
					++headptr->simulations;
					headptr->score += wasWin + wasDraw;
					headptr = headptr->parent;
				}

				break;
			}
			// If move doesnt exist create key for it and then set headptr to the node for key
			if (headptr->children.find(optimalMove) == headptr->children.end()) {
				headptr->children[optimalMove] = Node(headptr);
			}
			headptr = &(headptr->children[optimalMove]);
			totalMoves += 1;
		}
		tree.root.simulations++;
	}

	string bestMove;
	double bestRatio = -1;
	std::cout << "\nFINAL RESULTS:\n";
	for (auto it = tree.root.children.begin(); it != tree.root.children.end(); ++it) {

		std::cout << "Move = " << it->first  << ", simulations = " << it->second.simulations
							<< ", score = " << it->second.score << ", score/sim = " <<
							(double)it->second.score/(double)it->second.simulations << std::endl;
		if ((double)it->second.score/(double)it->second.simulations > bestRatio) {
			bestRatio = (double)it->second.score/(double)it->second.simulations;
			bestMove = it->first;
		}
	}
	return Move(bestMove, startBoard.get_next_move());
}

double uct(double score, double simulations, double parentsimulations) {
	return score / simulations + sqrt(2) * sqrt(log(parentsimulations) / simulations);
}
