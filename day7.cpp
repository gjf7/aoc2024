#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "utils.hpp"

using namespace std;

bool dfs(u64 target_sum, u64 current_sum, int index, vector<u64>& numbers) {
  if (index == numbers.size())
    return target_sum == current_sum;

  if (numbers[index] > target_sum) {
    return false;
  }

  return dfs(target_sum, current_sum + numbers[index], index + 1, numbers) ||
  dfs(target_sum, current_sum * numbers[index], index + 1, numbers);
}

int main() {
  ifstream f("day7.txt");
  if (!f) {
    cout << "failed to read input" << endl;
    return 1;
  }

  unsigned long ret = 0;
  for (string line; getline(f, line);) {
    vector<string> parts = split(line, ": ");

    vector<u64> numbers;
    vector<string> strs = split(parts[1], ' ');
    transform(strs.begin(), strs.end(), back_inserter(numbers), [](const string& str) { return stoll(str); });

    u64 sum = stoll(parts[0]);
    if (dfs(sum, 0, 0, numbers))
      ret += sum;
  }

  cout << "Day7 answer: " << ret << endl;

  return 0;
}
