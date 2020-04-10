#pragma once
#include <iostream>

#include "binType.h"
#include "completeWinnerTree.h"

void firstFitPack(int *objectSize, int numberOfObjects, int binCapacity) {
  // 输出箱子容量为binCapacity的最先适配装载
  // bjectSize[i]是物品i的大小

  int n = numberOfObjects;  // 物品数量

  // 初始化n个箱子和赢者树
  binType *bin = new binType[n + 1];
  for (int i = 1; i <= n; i++) bin[i].unusedCapacity = binCapacity;
  completeWinnerTree<binType> winTree(bin, n);

  // 将物品撞到箱子里
  for (int i = 1; i <= n; i++) {
    // 把物品i装入一个箱子
    // 找到第一个有足够容量的箱子
    int child = 2;  // 从根的左孩子开始搜索
    while (child < n) {
      int winner = winTree.winner(child);
      if (bin[winner].unusedCapacity < objectSize[i])  // 左子树没有箱子可以放下
        child++;                                       // 移到右子树
      child *= 2;
    }  // 循环结束以后child>=n必定是一个箱子的位置

    int binToUse;  // 设置为要使用的箱子
    child /= 2;    // 撤销向最后左孩子的移动
    if (child < n) {
      // 内部节点：一个比赛
      binToUse = winTree.winner(child);
      //  若binToUse是右孩子，则检查箱子binToUse-1(因为赢者树选出来的是未使用空间最大的箱子，其左箱子也有可能右足够的空闲放在obj【i】)
      // 即使binToUse是左孩子，检查箱子binToUse-1也不会有问题
      if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i])
        binToUse--;
    } else  // 当n是奇数当前节点有可能是一个外部节点 位置为n
      binToUse = winTree.winner(child / 2);

    std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
    bin[binToUse].unusedCapacity -= objectSize[i];
    winTree.rePlay(binToUse);
  }
};