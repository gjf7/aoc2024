#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include "utils.hpp"

using namespace std;

int main() {
  ifstream f("day5.txt");
  if (!f) {
    cout << "Read input error" << endl;
  }

  unordered_map<int, vector<pair<int, int>>> notebook;
  for (string line; getline(f, line);) {
    if (line.empty()) break;

    vector<string> parts = split(line, '|');
    int left = stoi(parts[0]);
    int right = stoi(parts[1]);

    notebook[left].emplace_back(left, right);
    notebook[right].emplace_back(left, right);
  }

  unsigned ret = 0;
  for (string line; getline(f, line);) {
    vector<string> updates = split(line, ',');
    
    int i = 0;
    for (; i < updates.size(); i++) {
      int num = stoi(updates[i]);
      
      vector<pair<int, int>>& rules = notebook[num];
      int j = 0;
      for (; j < rules.size(); j++) {
        const auto& [left, right] = rules[j];

        if (num == left) {
          // check left
          int k;
          for (k = i - 1; k >= 0; k--) {
            if (stoi(updates[k]) == right) break;
          }

          if (k >= 0) break;
        } else {
          // check right
          int k;
          for (k = i + 1; k < updates.size(); k++) {
            if (stoi(updates[k]) == left) break;
          }

          if (k < updates.size()) break;
        }
      }

      if (j < rules.size())
        break;
    }

    int n = updates.size();
    if (i == n) {
      // calc middle number 
      int a = stoi(updates[n / 2]);
      int b = stoi(updates[n / 2 - 1]);
      
      if (n % 2 == 0) {
        ret += (a + b) / 2;
      } else {
        ret += a;
      }
    }
  }

  cout << "Day5 answer: " << ret << endl;

  return 0;

}

