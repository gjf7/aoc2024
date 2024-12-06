#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum DIRECTION {
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  TOPLEFT,
  TOPRIGHT,
  BOTTOMLEFT,
  BOTTOMRIGHT,
  DIRECTION_END,
};

static const string WORD = "XMAS";

int dfs(vector<vector<char>>& input, DIRECTION direction, int row, int col, int level) {
  if (level >= 4 || row < 0 || row >= input.size() || col < 0 || col >= input[0].size())
    return 0;

  if (input[row][col] != WORD[level])
    return 0;

  if (level == 3)
    return 1;

  switch (direction) {
    case TOP:
      return dfs(input, direction, row - 1, col, level + 1);
    case BOTTOM:
      return dfs(input, direction, row + 1, col, level + 1);
    case LEFT:
      return dfs(input, direction, row, col - 1, level + 1);
    case RIGHT:
      return dfs(input, direction, row, col + 1, level + 1);
    case TOPLEFT:
      return dfs(input, direction, row - 1, col - 1, level + 1);
    case TOPRIGHT:
      return dfs(input, direction, row - 1, col + 1, level + 1);
    case BOTTOMLEFT:
      return dfs(input, direction, row + 1, col - 1, level + 1);
    case BOTTOMRIGHT:
      return dfs(input, direction, row + 1, col + 1, level + 1);
    default:
      return 0;
  }

  return 0;
}

int search_at(vector<vector<char>>& input, int row, int col) {
  int ret = 0;
  for (int dir = TOP; dir != DIRECTION_END; dir++) {
    ret += dfs(input, static_cast<DIRECTION>(dir), row, col, 0);
  }

  return ret;
}

int main() {
  ifstream f("day4.txt");
  if (!f)
    return 1;

  vector<vector<char>> input;
  for (string line; getline(f, line);) {
    vector<char> row;
    for (char c: line)
      row.push_back(c);
    input.push_back(row);
  }

  int ret = 0;
  int row_len = input.size();
  int col_len = input[0].size();
  for (int row = 0; row < row_len; row++) {
    for (int col = 0; col < col_len; col++) {
      ret += search_at(input, row, col);
    }
  }

  cout << "Day4 answer: " << ret << endl;

  return 0;
}

