#include <iostream>
#include <vector>
#include "position.h"
#include "board.h"
#include "piece.h"
#include "move.h"

int main(int argc, char *argv[])
{
  Position pos;

  std::vector<Move> moveVec;
  generateMoves(pos, moveVec, cWhite);
  std::cout << "LEGAL MOVES: " << std::endl;
  for (auto it = moveVec.begin(); it != moveVec.end(); ++it) {
    std::cout << it->notation() << std::endl;
  }
  return 0;
}
