#include <iostream>

#include "arrayStack.h"
#include "towersOfHanoi.h"

using namespace std;

int main() {
  arrayStack<int> towers[4];
  int numOfDisks = 0;
  cout << "enter the number of disks" << endl;
  cin >> numOfDisks;
  towerOfHanoiWithStack(numOfDisks, 1, 2, 3);

  cout << "\n\n Rescursion with no stack : \n";
  towerOfHanoi(numOfDisks, 1, 2, 3);
};