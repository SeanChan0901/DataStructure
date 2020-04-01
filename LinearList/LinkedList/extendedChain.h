#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include "ChainNode.h"
#include "chain.h"
#include "extendedLinearList.h"
#include "myExceptions.h"

template <typename T>
class extendedChain : public extendedLinearList<T>, public chain<T> {
 public:
  // 构造函数，复制构造，析构函数
  extendedChain(int initial_capacity = 10) : chain<T>(initial_capacity){};  // 直接用chain的
  extendedChain(const extendedChain<T>& c) : chain<T>(c){};  // 直接用chain的

  // ADT
  bool empty() const { return chain<T>::empty(); };
  int size() const { return chain<T>::size(); };
  T& get(int the_index) const { return chain<T>::get(the_index); };
  int indexOf(const T& the_element) const {
    return chain<T>::indexOf(the_element);
  };
  void erase(int the_index);
  void insert(int the_index, const T& the_element);
  void output(std::ostream& out) const { chain<T>::output(out); };
  void clear();
  void push_back(const T& the_element);

  // 保护成员中，firstNode和listSize和checkIndex都有了，拓展以下就可以了
 protected:
  chainNode<T>* lastNode;
};


// erase
template <typename T>
void extendedChain<T>::erase(int the_index) {
  chain<T>::checkIndex(the_index);     // 判断合法性
  chainNode<T>* deleteNode;  // 要删除的节点的指针
  if (the_index == 0) {      // 如果删除的是表首节点
    deleteNode = chain<T>::firstNode;
    chain<T>::firstNode = chain<T>::firstNode->next;  // 更新firstNode
  } else {
    chainNode<T>* p = chain<T>::firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // 找到要删除节点的前驱节点
      p = p->next;
    }
    deleteNode = p->next;        // 找到要删除的节点
    p->next = deleteNode->next;  // 脱链
    if (deleteNode == lastNode) lastNode = p;  // 更新最后一个节点
  }
  chain<T>::list_size--;
  delete deleteNode;
};

// insert
template <typename T>
void extendedChain<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > chain<T>::list_size) {  // 判断索引合法性
    std::ostringstream s;
    s << "index = " << the_index << " size = " << chain<T>::list_size;
    throw IllegalIndex(s.str());
  }

  if (the_index == 0) {
    chain<T>::firstNode = new chainNode<T>(the_element, chain<T>::firstNode);  // 第0个位置插
  } else {
    chainNode<T>* p = chain<T>::firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // 找到要插入位置的前一个位置
      p = p->next;
    }
    p->next = new chainNode<T>(the_element, p->next);
    if (chain<T>::list_size == the_index)  // 如果要插到最后的位置
      lastNode = p->next;
  }
  chain<T>::list_size++;
};

// clear
template <typename T>
void extendedChain<T>::clear() {
  while (chain<T>::firstNode != NULL) {
    chainNode<T>* nexteNode = chain<T>::firstNode->next;
    delete chain<T>::firstNode;
    chain<T>::firstNode=nexteNode;
  }
  chain<T>::list_size = 0;
};

// push_back
template <typename T>
void extendedChain<T>::push_back(const T& the_element) {
  chainNode<T>* newNode = new chainNode<T>(the_element, NULL);  // 新建节点
  if (chain<T>::firstNode == NULL)
    chain<T>::firstNode = lastNode = newNode;
  else {
    lastNode->next = newNode;
    lastNode = newNode;
  }
  chain<T>::list_size++;
};