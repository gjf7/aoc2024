#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils.hpp"

using namespace std;

int main() {
  fstream f("day9.txt");
  if (!f) {
    cout << "Failed to open input" << endl;
    return 1;
  }

  string line;
  getline(f, line);
  vector<string> map;
  int cursor = 0;
  for (int i = 0; i < line.size(); i++) {
    if (i % 2 == 0) {
      map.insert(map.end(), line[i] - '0', to_string(cursor++));
    } else {
      map.insert(map.end(), line[i] - '0', ".");
    }
  }

  int start = -1;
  int end = map.size();
  while (start < end) {
    while (map[++start] != ".") {};

    while (map[--end] == ".") {};

    if (start < end)
      swap(map[start], map[end]);
  }

  // checksum
  u64 ret = 0;
  size_t i = -1;
  while (map[++i] != ".") {
    ret += i * stoi(map[i]);
  }

  cout << "Day9 answer: " << ret << endl;

  return 0;
}

