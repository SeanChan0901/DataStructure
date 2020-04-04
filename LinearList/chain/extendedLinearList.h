#pragma once
#include <iostream>
#include "LinearList.h"

template <typename T>
class extendedLinearList : LinearList<T> {
 public:
  virtual ~extendedLinearList(){};
  virtual void clear() = 0;  // �������
  virtual void push_back(const T& the_element) = 0;  // �嵽��β
};