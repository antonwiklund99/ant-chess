#ifndef MCST_GUARD
#define MCST_GUARD

#include <map>
#include <string>
#include <vector>
#include "move.h"
#include "board.h"

class Node {
 public:
	int simulations;
	int wins;
	std::map<std::string, Node> children;
	Node* parent;

	Node(Node*);
	Node() {};
};

struct Tree {
	Node root;

  Tree() : root(NULL) {}
};

Move computeBestMove(const Board&);
double uct(double, double, double);
#endif
