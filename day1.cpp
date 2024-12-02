#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "utils.hpp"

int main() {
  std::ifstream f("day1.txt");
  
  if (!f) {
    std::cout << "failed to open input\n";
    return 1;
  }

  std::vector<int> list1, list2;
  for (std::string line; std::getline(f, line);) {
    list1.push_back(std::stoi(split(line, "   ")[0]));
    list2.push_back(std::stoi(split(line, "   ")[1]));
  }
  
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  unsigned int ret = 0;
  for (int i = 0; i < list1.size(); i++) {
    ret += std::abs(list1[i] - list2[i]);
  }

  std::cout << "Day1 answer: " << ret << std::endl;
    
  return 0;
}
