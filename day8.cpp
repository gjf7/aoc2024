#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
  fstream f("day8.txt");
  if (!f) {
    cout << "Failed to open input" << endl;
    return 1;
  }

  unordered_map<char, vector<pair<int, int>>> antennas_map;

  int row = 0;
  int column = 0;
  for (string line; getline(f, line);) {
    for (int col = 0; col < line.size(); col++) {
      char frequency = line[col];
      if (frequency == '.') continue;
      
      antennas_map[frequency].emplace_back(row, col);
    }

    row += 1;

    if (!column)
      column = line.size();
  }


  vector<vector<int>> notebook(row, vector<int>(column, 0));
  for (const auto& [_, antennas]: antennas_map) {
    for (int i = 0; i < antennas.size(); i++) {
      for (int j = i + 1; j < antennas.size(); j++) {
        auto [y1, x1] = antennas[i];
        auto [y2, x2] = antennas[j];
        int d1 = abs(x1 - x2);
        int d2 = abs(y1 - y2);
        pair<int, int> antinode1, antinode2;
        if (d1 != 0 && static_cast<double>(y1 - y2) / static_cast<double>(x1 - x2) < 0) {
          antinode1 = { min(x1, x2) - d1, max(y1, y2) + d2};
          antinode2 = { max(x1, x2) + d1, min(y1, y2) - d2};
        } else {
          antinode1 = { min(x1, x2) - d1, min(y1, y2) - d2};
          antinode2 = { max(x1, x2) + d1, max(y1, y2) + d2};
        }
        
        auto [a1_x, a1_y] = antinode1;
        if (a1_y >= 0 && a1_y < row && a1_x >= 0 && a1_x < column) {
          notebook[a1_y][a1_x] = 1;
        }

        auto [a2_x, a2_y] = antinode2;
        if (a2_y >= 0 && a2_y < row && a2_x >= 0 && a2_x < column) {
          notebook[a2_y][a2_x] = 1;
        }
      }
    }
  }

  int ret = 0;
  for (auto const& v: notebook) {
    for (int const n: v)
      ret += n;
  }
  cout << "Day8 answer: " << ret << endl;

  return 0;
}

