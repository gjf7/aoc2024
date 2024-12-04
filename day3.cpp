#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

int main() {
  ifstream f("day3.txt");

  if (!f) {
    cout << "Failed to open input\n";
    return 1;
  }

  stringstream ss;
  ss << f.rdbuf();
  string input = ss.str();

  regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))", regex::icase | regex::multiline);
  auto words_begin = sregex_iterator(input.begin(), input.end(), pattern);
  auto words_end = sregex_iterator();

  uint64_t ret = 0;
  for (sregex_iterator i = words_begin; i != words_end; i++) {
    smatch match = *i;
    int x = stoi(match.str(1));
    int y = stoi(match.str(2));

    ret += x * y;
  }

  cout << "Day3 answer: " << ret << endl;

  return 0;
}
