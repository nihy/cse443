#include <iostream>

using namespace std;

int main() {
  int a, b, c;

  cout << "Enter 3 integers: ";
  cin >> a >> b >> c;

  cout << "largest = " << max(max(a, b), c) << endl;
  cout << "smallest = " << min(min(a, b), c) << endl;

  return 0;
}