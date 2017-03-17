// Copyright 2016 Henry Ni

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>
#include <iterator>
#include <climits>
#include <string>

inline bool comp(int& x, int& y) {
  return x < y;
}

int main(int argc, char* argv[]) {
  std::string cmd = argv[1];
  const int VECTOR_SIZE = 100;
  std::vector<int> v(VECTOR_SIZE);
  std::generate(v.begin(), v.end(), std::rand);

  if (argc > 1 && cmd == "inline") {
    for (int i = 0; i < 18000000; i++) {
      std::sort(v.begin(), v.end(), comp);
    }
  } else {
    for (int i = 0; i < 18000000; i++) {
      std::sort(v.begin(), v.end(), [](int x, int y){return x < y;});
    }
  }
return 0;
}
