#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "LinearList.h"
#include "myExceptions.h"

template <typename T>
class VectorList : public LinearList<T> {
 public:
  // 构造函数和析构函数
  VectorList(int initial_capacity = 10);
  VectorList(const VectorList<T> &);  // 复制构造函数的变量名在声明时可以省略
  ~VectorList() { delete element; };  

  // 功能函数
  bool empty() const { return element->empty(); };
  int size() const { return (int)element->size(); };
  T &get(int the_index) const;
  int indexOf(const T &the_element) const;
  void erase(int the_index);
  void insert(int the_index, const T &the_element);
  void output(std::ostream& out) const;

  // 新增的方法
  int capacity() const { return element->capacity(); };

  // 线性表的起始和结束位置的迭代器
  typedef typename std::vector<T>::iterator iterator;
  iterator begin() { return element->begin(); };
  iterator end() {
    return element->end();
  };  // end（）的位置是最后一个元素的后面一个位置

 protected:
  void checkIndex(int the_index) const;  // 查看索引是否合法，若不合法则抛出异常
  std::vector<T> *element;  // 一个指向vector对象的指针
};

// 构造函数
template <typename T>
VectorList<T>::VectorList(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "initial capacity = " << initial_capacity << "Must be > 0";
    throw IllegalParameterValue(s.str());
  }

  element = new std::vector<T>;
  element->reserve(initial_capacity);  // 增加容量的函数
};

// 复制构造
template<typename T>
VectorList<T>::VectorList(const VectorList<T> &the_list) {
  element = new std::vector<T>((*the_list.element));
};


// 查看索引函数
template <class T>
void VectorList<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= element->size()) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << element->size();
    throw IllegalIndex(s.str());
  }
};

// get
template <typename T>
T &VectorList<T>::get(int the_index) const {
  checkIndex(the_index);  // 查看索引合法性
  return (*element)[the_index];
};


// indexOf
template <typename T>
int VectorList<T>::indexOf(const T &the_element) const {
  int the_index =
      (int)((std::find(element->begin(), element->end(), the_element)) -
            (element->begin()));
  if (the_index == element->size())
    return -1;
  else
    return the_index;
};


//  erase
template <typename T>
void VectorList<T>::erase(int the_index) {
  checkIndex(the_index);
  element->erase(element->begin() + the_index);
};

// insert
template <typename T>
void VectorList<T>::insert(int the_index, const T &the_element) {
  if (the_index < 0 || the_index > element->size()) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << element->size();
    throw IllegalIndex(s.str());
  }
  element->insert(element->begin()+the_index,the_element);
};


// output
template<typename T>
void VectorList<T>::output(std::ostream &out) const {
  copy(element->begin(), element->end(),
       std::ostream_iterator<T>(out, " "));
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const VectorList<T> &x) {
  x.output(out);
  return out;
};