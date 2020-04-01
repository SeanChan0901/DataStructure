#pragma once
#include <iostream>
#include "LinearList.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <sstream>

template <typename T>
class circularListWithHeader : public LinearList<T> {
 public:
  circularListWithHeader(int initial_capacity = 10);
  circularListWithHeader(const circularListWithHeader<T>&);
  ~circularListWithHeader();

  // ADT
  bool empty() const { return list_size == 0; };
  int size() const { return list_size; };
  T& get(int the_index) const;
  int indexOf(const T& the_element) const;
  void erase(int the_index);
  void insert(int the_index, const T& the_element);
  void output(std::ostream& out) const;

 private:
  void checkIndex(int the_index) const;
  chainNode<T>* headerNode;  // 头节点
  int list_size;
};

// 判断索引合法性
template <typename T>
void circularListWithHeader<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// 构造函数
template <typename T>
circularListWithHeader<T>::circularListWithHeader(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "initial capacity = " << initial_capacity << "must be > 0";
    throw IllegalParameterValue(s.str());
  }
  headerNode = new chainNode<T>();  // 构造头节点，里面啥都不放
  headerNode->next = headerNode;
  list_size = 0;
};

template <typename T>
circularListWithHeader<T>::circularListWithHeader(
    const circularListWithHeader<T>& the_list) {
  list_size = the_list.list_size;
  headerNode = new chainNode<T>();  // 创建头节点
  if (list_size == 0) {
    headerNode->next = headerNode;  // 循环
    return;                         // 如果是空表直接返回
  }
  //非空表
  chainNode<T>* sourceNode = the_list.headerNode->next;
  chainNode<T>* targetNode = headerNode;
  while (sourceNode != the_list.headerNode) {
    targetNode->next = new chainNode<T>(sourceNode->element);  // 复制节点
    targetNode = targetNode->next;
    sourceNode = sourceNode->next;
  }
  targetNode->next = headerNode;
};

// get
template <typename T>
T& circularListWithHeader<T>::get(int the_index) const {
  checkIndex(the_index);  // 判断索引合法性
  chainNode<T>* currentNode = headerNode->next;
  for (int i = 0; i < the_index; i++) {
    if (i != the_index) currentNode = currentNode->next;
  }
  return currentNode->element;
};

// indexOf 找不到返回-1
template<typename T>
int circularListWithHeader<T>::indexOf(const T& the_element) const {
  // 元素放入头节点
  headerNode->element = the_element;

  // 在链表中搜索元素
  chainNode<T>* currentNode = headerNode->next;
  int index = 0;  // 当前索引
  while (currentNode->element != the_element) {
    currentNode = currentNode->next;
    index++;
  }
  if (currentNode == headerNode) {  // 如果回到头节点了
    return -1;
  } else {
    return index;
  }
};

template<typename T>
void circularListWithHeader<T>::erase(int the_index) {
  checkIndex(the_index);  // 查看索引合法性
  chainNode<T>* deleteNode = headerNode->next;
  if (the_index == 0) {
    headerNode->next = deleteNode->next;
  } else {
    chainNode<T>* p = headerNode->next;
    for (int i = 0; i < the_index - 1; i++) {  // 找到要删除的节点的前驱
      p = p->next;
    }
    deleteNode = p->next;  // 找需要被删除的节点
    p->next = deleteNode->next;  // 脱链
  }
  list_size--;
  delete deleteNode;
};

template<typename T>
void circularListWithHeader<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > list_size) {  // 判断索引合法性
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
  if (the_index == 0) {
    headerNode->next =
        new chainNode<T>(the_element, headerNode->next);  //插入第0个位置
  } else {
    chainNode<T>* p = headerNode->next;
    for (int i = 0; i < the_index - 1; i++) {
      p = p->next;
    }
    p->next = new chainNode<T>(the_element, p->next);
  }
  list_size++;
};

// output
template <typename T>
void circularListWithHeader<T>::output(std::ostream& out) const {
  for (chainNode<T>* currentNode = headerNode->next; currentNode != headerNode;
       currentNode = currentNode->next) {
    out << currentNode->element << " ";
  }
};

// <<
template <typename T>
std::ostream& operator<<(std::ostream& out,
                         const circularListWithHeader<T>& x) {
  x.output(out);
  return out;
};

template<typename T>
circularListWithHeader<T>::~circularListWithHeader() {
  chainNode<T>* deleteNode = headerNode->next;
  while (deleteNode != headerNode) {
    headerNode->next = deleteNode->next;
    delete deleteNode;
    deleteNode = headerNode->next;
  }
};