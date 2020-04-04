#pragma once
#include <iostream>

template <class T>
class LinearList {  // 线性表的顺序表实现（数组实现）
 public:
  virtual ~LinearList(){};  // 析构函数设置为虚函数使得对象能够找到自己类的析构函数
  virtual bool empty() const = 0;  // 是否为空，空则返回true
  virtual int size() const = 0;    // 返回线性表元素个数
  virtual T& get(int the_index) const = 0;  // 返回索引对应的元素
  virtual int indexOf(const T& the_element) const = 0;  // 返回元素第一次出现的索引值
  virtual void erase(int the_index) = 0;  // 删除索引为the_index的元素
  virtual void insert(
      int the_index,
      const T&
          the_element) = 0;  // 将元素the_element插入到索引the_index的位置上
  virtual void output(std::ostream& out) const = 0;  // 把线性表插入输出流
};