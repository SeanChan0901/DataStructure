#pragma once
#include <iostream>

#include "binarySearchTreeWithVisit.h"

void histogramWithArray() {
  // 非负整形值的直方图
  int n;  // 元素个数
  int r;  // 0到r之间的值
  std::cout << "Enter number of elements and range" << std::endl;
  std::cin >> n >> r;
  // 生成直方图数组h
  int *h = new int[r + 1];

  // 数组初始化为0
  for (int i = 0; i <= r; i++) {
    h[i] = 0;
  }

  // 输入数据
  for (int i = 1; i <= n; i++) {
    int key;  // 输入值
    std::cout << "Enter element " << i << std::endl;
    std::cin >> key;
    h[key]++;  // 出现次数
  }

  // 输出直方图
  std::cout << "Distinct elements and frequencies are" << std::endl;
  for (int i = 0; i <= r; i++)
    if (h[i] != 0) std::cout << i << " " << h[i] << std::endl;
};

// 用二叉搜索树表示直方图
void histogramWithBSTree() {
  // 非负整形值的直方图
  int n;  // 元素个数
  std::cout << "Enter number of elements" << std::endl;
  std::cin >> n;
  binarySearchTreeWithVisit<int, int> theTree;

  // 输入元素，插入树
  for (int i = 1; i <= n; i++) {
    std::pair<int, int> thePair;
    std::cout << "Enter element " << i << std::endl;
    std::cin >> thePair.first;
    thePair.second = 1;
    // 插入树，如果不存在这样的关键字则插入这个节点，否则访问这个节点，增加其频率
    theTree.insert(thePair, add1);
  }

  // 输出关键字和频率
  std::cout << "Distinct elements and frequencies are " << std::endl;
  theTree.ascend();
};