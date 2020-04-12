#pragma once
#include <iostream>

template <typename T>
class queue {
 public:
  virtual ~queue() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual T& front() const = 0;  // 返回队首元素
  virtual T& back() const = 0;  // 返回队尾元素
  virtual void pop() = 0;       // 删除队首元素
  virtual void push(const T& the_element) = 0;  // 把元素element加到队尾
};