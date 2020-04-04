#pragma once
#include <iostream>
#include "LinearList.h"

template <typename T>
class extendedLinearList : LinearList<T> {
 public:
  virtual ~extendedLinearList(){};
  virtual void clear() = 0;  // 清空链表
  virtual void push_back(const T& the_element) = 0;  // 插到表尾
};