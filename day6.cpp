#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main() {
  ifstream f("day6.txt");
  if (!f) {
    cout << "Failed to open input" << endl;
    return 1;
  }
  vector<vector<char>> map;
  for (string line; getline(f, line);) {
    map.emplace_back(line.begin(), line.end());
  }

  optional<pair<int, int>> start_point;
  vector<vector<int>> notebook(map.size(), vector<int>(map[0].size(), 0));

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[j].size(); j++) {
      if (map[i][j] == '^') {
        start_point = make_pair(i, j);
        map[i][j] = '.';
        notebook[i][j] = 1;
        break;
      }
    }

    if (start_point) break;
  }

  pair<int, int> guard = make_pair(start_point->first, start_point->second);
  while (true) {
    // top
    int i = guard.first - 1;
    for (; i >= 0; i--) {
      if (map[i][guard.second] == '#') {
        break;
      }
      guard.first = i;
      notebook[guard.first][guard.second] = 1;
    }
    if (i < 0)
      break;

    // right
    int j = guard.second + 1;
    for (; j < map[0].size(); j++) {
      if (map[guard.first][j] == '#') {
        break;
      }
      guard.second = j;
      notebook[guard.first][guard.second] = 1;
    }
    if (j >= map[0].size())
      break;

    // bottom
    int k = guard.first + 1;
    for (; k < map.size(); k++) {
      if (map[k][guard.second] == '#') {
        break;
      }
      guard.first = k;
      notebook[guard.first][guard.second] = 1;
    }
    if (k >= map.size())
      break;
    
    // left
    int z = guard.second - 1;
    for (; z >= 0; z--) {
      if (map[guard.first][z] == '#') {
        break;
      }
      guard.second = z;
      notebook[guard.first][guard.second] = 1;
    }
    if (z < 0)
      break;
  }

  int ret = 0;
  for (const auto& row: notebook) {
    ret += accumulate(row.begin(), row.end(), 0);
  }

  cout << "Day6 answer: " << ret << endl;

  return 0;
}

