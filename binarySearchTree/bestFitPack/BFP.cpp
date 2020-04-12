#include <iostream>

#include "bestFitPack.h"

using namespace std;

int main() {
  cout << "Enter number of objects and bin capacity" << endl;
  int numberOfObjects, binCapacity;
  cin >> numberOfObjects >> binCapacity;
  if (numberOfObjects < 2) {
    cout << "Too few objects" << endl;
    exit(1);
  }

  // 输入物品大小objectSize[1:numberOfObjects]
  int *objectSize = new int[numberOfObjects + 1];
  for (int i = 1; i <= numberOfObjects; i++) {
    cout << "Enter space requirement of object " << i << endl;
    cin >> objectSize[i];
    if (objectSize[i] > binCapacity) {
      cout << "Object too large to fit in a bin" << endl;
      exit(1);
    }
  }

  // output the packing
  bestFitPack(objectSize, numberOfObjects, binCapacity);
  return 0;
};