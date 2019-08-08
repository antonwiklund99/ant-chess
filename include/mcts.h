#ifndef MCST_GUARD
#define MCST_GUARD

#include <map>
#include <string>
#include <vector>
#include "move.h"
#include "board.h"

class mctsNode {
 public:
	int simulations;
	int score;
	std::map<std::string, mctsNode> children;
	mctsNode* parent;

	mctsNode(mctsNode*);
	mctsNode() {};
};

struct mctsTree {
	mctsNode root;

  mctsTree() : root(NULL) {}
};

Move computeBestMove(const Board&);
double uct(double, double, double);
#endif
