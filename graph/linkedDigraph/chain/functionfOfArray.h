#pragma once
#include <iostream>
#include <algorithm>
#include <math.h>
#include "error.h"

template<class T>
void ChangeLength1D(T*& a, int old_length, int new_length) {  
  if (new_length < 0) error("new length must be >= 0");  // 新数组长度必须大于零
  T* temp = new T[new_length];                           // 新数组
  int number = std::min(old_length, new_length);  // 确认需要复制的元素个数
  std::copy(a, a + number, temp);  // 请查看迭代器中end()指向的到底是那个位置
  delete []a;
  a = temp;
};  // 更改一维数组的长度