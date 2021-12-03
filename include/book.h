#include <string>
#include <unordered_map>
#include <move.h>
#include <iterator>

namespace Book {
  void addEntry(std::string);
  void initBook();
  bool contains(uint64_t hash);
  Move& get(uint64_t);
}