
#pragma once
#include <iostream>

template <typename K, typename E>
class bsTree {
 public:
  virtual ~bsTree(){};
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual std::pair<const K, E>* find(const K&) const = 0;
  virtual void erase(const K&) = 0;
  virtual void insert(const std::pair<const K, E>&) = 0;
  virtual void ascend() = 0;  // 关键字升序输出所有数对
};