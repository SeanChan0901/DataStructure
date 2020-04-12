#include <iostream>

#include "dBinarySearchTreeWithGE.h"

void bestFitPack(int *objectSzie, int numberOfObjects, int binCapacity) {
  // 输出容量为binCapacity的最优箱子匹配
  // objectSize数组里面装的是物品的大小[1:numberOfObjects]
  int n = numberOfObjects;
  int binuUesd = 0;
  dBinarySearchTreeWithGE<int, int> theTree;  // 箱子容量树
  std::pair<int, int> theBin;

  // 将物品逐个装箱
  for (int i = 1; i <= n; i++) {
    // 将物品i装箱
    // 寻找最佳匹配的箱子
    std::pair<const int, int> *bestBin = theTree.findGE(objectSzie[i]);
    if (bestBin == NULL) {
      // 没有容量足够大的箱子，找一个新箱子
      theBin.first = binCapacity;
      theBin.second = ++binuUesd;  // 标记已启用了几个箱子
    } else {
      // 从树中删除最匹配的箱子，
      theBin = (*bestBin);
      theTree.erase(bestBin->first);
    }

    std::cout << " Pack object " << i << " in bin " << theBin.second
              << std::endl;

    // 讲箱子再插入到树中，除非箱子已满
    theBin.first -= objectSzie[i];
    if (theBin.first > 0) theTree.insert(theBin);
  }
};