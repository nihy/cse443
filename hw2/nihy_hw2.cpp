// Copyright (C) 2016 ?????

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <utility>

using namespace std;

void sortDigits(int target, int digit, string& s) {
  int repl = digit;
  if (digit < target) {
    for (int i = digit; i < target; i++) {
      swap(s[repl], s[repl+1]);
      repl++;
    }
  }
  else if (digit > target) {
    for (int i = digit; i > target; i--) {
      swap(s[repl], s[repl-1]);
      repl--;
    }
  }
}

void gatherDigits(std::string& s, const int pos) {
    // Implement this method! You may introduce additional methods as
    // needed

    // search string for digits, swap and increment int index var
  int int_index = pos;
  for (int i = 0; i < s.length(); i++) {
    if (isdigit(s[i]) && i != pos)  {
      sortDigits(int_index, i, s); 
      int_index++;
      cout << s << endl;
    }

  }
}



// --------------------------------------------------------------
//        DO  NOT  MODIFY  CODE  BELOW  THIS  LINE
// --------------------------------------------------------------

int main() {
  std::string str;
  int pos = 0;
  do {
    std::cout << "Enter gather position (-1 to quit) and string:\n";
    std::cin >> pos;
    if (pos != -1) {
      std::cin >> str;
      gatherDigits(str, pos);
      std::cout << "Gathered @ " << pos << ": " << str << std::endl;
    }
  } while (pos != -1);
  return 0;
}
