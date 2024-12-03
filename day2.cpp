#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
#include "utils.hpp"

using namespace std;

int main() {
  ifstream f("day2.txt");

  if (!f) {
    cout << "failed to open input\n";
    return 1;
  }

  int ret = 0;
  for (string line; getline(f, line);) {
    vector<string> report = split(line, ' ');
    
    bool valid = true;
    bool increasing = stoi(report[1]) - stoi(report[0]) > 0;
    for (int i = 0; i < report.size() - 1; i++) {
      int diff = stoi(report[i + 1]) - stoi(report[i]);

      if (increasing &&  diff >= 1 && diff <= 3)
        continue;

      if (!increasing &&  diff >= -3 && diff <= -1)
        continue;

      valid = false;
    }

    if (valid)
      ret += 1;
  }

  cout << "Day2 answer: " << ret << endl;

  return 0;
}

