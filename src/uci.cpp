#include "uci.h"
#include "bitboards.h"
#include "minimax.h"
#include "position.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int indexOf(vector<Move> &v, const string &s) {
  for (size_t i = 0; i < v.size(); i++) {
    if (v[i].notation() == s)
      return i;
  }
  return -1;
}

namespace UCI {
namespace {
string info = "id name   Achess\nid author Anton Wiklund\n";
Position *pos;
bool debug = false;
std::ofstream myfile;

void position(const vector<string> &args) {
  size_t movesStart;
  delete pos;
  if (args[1] == "fen") {
    pos = new Position(args[2] + " " + args[3] + " " + args[4] + " " + args[5] +
                       " " + args[6] + " " + args[7]);
    movesStart = 9;
  } else if (args[1] == "startpos") {
    pos = new Position();
    movesStart = 3;
  } else
    throw new std::invalid_argument(
        "unknown position command, specify either fen or startpos");

  if (debug) {
    myfile << "Original position\n"
           << pos->board << "turn = " << (pos->turn == cWhite ? "w" : "b")
           << "\nhalfMoveClock = " << pos->halfMoveClock
           << "\nfullMoveNumber = " << pos->fullMoveNumber << endl;
  }
  if (args.size() > movesStart && args[movesStart - 1] == "moves") {
    vector<Move> m;

    while (movesStart < args.size()) {
      generateMoves(*pos, m);
      int i = indexOf(m, args[movesStart]);
      if (i == -1) {
        std::cout << "move: " << args[movesStart] << " is not valid?"
                  << std::endl;
        throw new std::invalid_argument("move : " + args[movesStart] +
                                        " is not valid");
      }
      pos->makeMove(m[i]);
      movesStart++;
    }
  }

  if (debug) {
    myfile << "After moves\n"
           << pos->board << "turn = " << (pos->turn == cWhite ? "w" : "b")
           << "\nhalfMoveClock = " << pos->halfMoveClock
           << "\nfullMoveNumber = " << pos->fullMoveNumber << endl;
  }
}

void go(const vector<string> &args) {
  int depth = 5, wtime = -1, btime = -1, winc = -1, binc = -1, movestogo = -1,
      nodes = -1, mate = -1, movetime = -1;
  bool ponder = false, infinite = false;
  vector<Move> m = legalMoves(*pos);
  vector<Move> searchMoves;
  for (size_t i = 1; i < args.size(); i++) {
    if (args[i] == "searchmoves") {
      int idx;
      while (++i < args.size() && (idx = indexOf(m, args[i])) != -1)
        searchMoves.push_back(m[idx]);
    } else if (args[i] == "ponder")
      ponder = true;
    else if (args[i] == "wtime")
      wtime = std::stoi(args[++i]);
    else if (args[i] == "btime")
      btime = std::stoi(args[++i]);
    else if (args[i] == "winc")
      winc = std::stoi(args[++i]);
    else if (args[i] == "binc")
      binc = std::stoi(args[++i]);
    else if (args[i] == "movestogo")
      movestogo = std::stoi(args[++i]);
    else if (args[i] == "depth")
      depth = std::stoi(args[++i]);
    else if (args[i] == "nodes")
      nodes = std::stoi(args[++i]);
    else if (args[i] == "mate")
      mate = std::stoi(args[++i]);
    else if (args[i] == "movetime")
      movetime = std::stoi(args[++i]);
    else if (args[i] == "infinite")
      infinite = true;
  }
  string bm;
  myfile << "searching on this board" << pos->board;

  bm = minimaxComputeBestMove(*pos, depth).notation();
  myfile << "bestmove " << bm << endl;
  cout << "bestmove " << bm << endl;
}
} // namespace

void run() {
  myfile.open("log.txt", std::ios_base::app);
  Magic::initMagic();
  Bitboards::initEasyBitboards();
  debug = true;
  string input;
  vector<string> splitted;
  while (true) {
    getline(std::cin, input);
    myfile << input << std::endl;
    split(input, splitted, ' ');
    if (input == "quit" || input == "exit") {
      delete pos;
      myfile.close();
      return;
    } else if (input == "uci") {
      cout << info << "uciok" << endl;
    } else if (splitted[0] == "debug") {
      if (splitted[1] == "on")
        debug = true;
      else if (splitted[1] == "off")
        debug = false;
    } else if (input == "isready") {
      cout << "readyok" << endl;
    } else if (splitted[0] == "position") {
      position(splitted);
    } else if (splitted[0] == "go") {
      go(splitted);
    } else if (splitted[0] == "stop") {
      // stop.store(true);
    } else if (splitted[0] == "setoption") {
      std::cout << "info str Engine has no options" << std::endl;
    } else if (splitted[0] == "perft") {
      uint64_t nodes = 0;
      for (auto m : legalMoves(*pos)) {
        pos->makeMove(m);
        uint64_t i = perft(std::stoi(splitted[1]) - 1, *pos);
        nodes += i;
        cout << m.notation() << ": " << i << endl;
        pos->unmakeMove(m);
      }
      cout << "Nodes: " << nodes << endl;
    }
  }
}
} // namespace UCI
