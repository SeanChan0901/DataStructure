#include <iostream>

#include "firstFitPack.h"
using namespace std;

int main() {
  int n, binCapacity;  // 物品数，箱子树
  cout << "Enter number of objects and bin capacity" << endl;
  cin >> n >> binCapacity;
  if (n < 2) {
    cout << "Too few objects" << endl;
    exit(1);
  }
  int *objectSize = new int[n + 1];

  for (int i = 1; i <= n; i++) {
    cout << "Enter space requirement of object " << i << endl;
    cin >> objectSize[i];
    if (objectSize[i] > binCapacity) {
      cout << "Object too large to fit in a bin" << endl;
      exit(1);
    }
  }
  firstFitPack(objectSize, n, binCapacity);
  return 0;
}