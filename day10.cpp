#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using namespace std;

int dfs(vector<vector<int>>const & map, int row, int column) {
  if (map[row][column] == 9) {
    return 1;
  }

  vector<pair<int, int>> direction { {1, 0 }, {-1, 0}, {0, 1}, {0, -1}};

  int ret = 0;
  for (int i = 0; i < 4; i++) {
    int new_row = row + direction[i].first;
    int new_column = column + direction[i].second;

    if (new_row < 0 || new_row >= map.size())
      continue;

    if (new_column < 0 || new_column >= map[0].size())
      continue;

    if (map[new_row][new_column] != map[row][column] + 1)
      continue;

    ret += dfs(map, new_row, new_column);
  }

  return ret;
}

int main() {
  fstream f("day10.txt");
  if (!f)
    return 1;

  vector<vector<int>> map;
  for (string line; getline(f, line);) {
    map.emplace_back();
    map.back().reserve(line.size());
    for (char c: line) {
      map.back().push_back(c - '0');
    }
  }

  // Find start point
  int ret = 0;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0) {
        ret += dfs(map, i, j);
      }
    }
  }


  cout << "Day10 answer: " << ret << endl;

  return 0;
}

