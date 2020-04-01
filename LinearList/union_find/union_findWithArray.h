#pragma once
#include <iostream>

int *equivClass, n;
void initialize(int numberOfElements) {
  // 用每个类的一个元素初始化numbersOfElements个类
  n = numberOfElements;
  equivClass = new int[n + 1];  // 这么多个独立的等价类
  for (int e = 1; e <= n; e++) {
    equivClass[e] = e;
  }
}

// 输入的是等价类
void unite(int class_a, int class_b) {
  // 合并类a和b
  // 假设类A和B不等价
  for (int k = 1; k <= n; k++) {  // 查找所有元素，
    if (equivClass[k] == class_b) {  // 假设这么多个等价类里面，有与b等价的
      equivClass[k] = class_a;  // 合并a与b，令等价类b中的所有元素类型等于a
    }
  }
};

int find(int the_element) {  // 找某个元素的等价类
  return equivClass[the_element];
};