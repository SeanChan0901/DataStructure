#pragma once
#include <iostream>

#include "dictionary.h"
#include "pairNode.h"

template <typename K, typename E>
class sortedChain {
 protected:
  pairNode<K, E>* firstNode;  // 表头
  int dSize;                  // 长度
 public:
  sortedChain() {
    firstNode = NULL;
    dSize = 0;
  };
  ~sortedChain();

  bool empty() const { return dSize == 0; };
  int size() const { return dSize; };
  std::pair<const K, E>* find(const K&) const;
  void erase(const K&);
  void insert(const std::pair<const K, E>&);
  void output(std::ostream& out) const;
};

// 析构函数
template <typename K, typename E>
sortedChain<K, E>::~sortedChain() {
  while (firstNode != NULL) {
    pairNode<K, E>* nextNode = firstNode->next;
    delete firstNode;
    firstNode = nextNode;
  }
}

//  查找键值对
template <typename K, typename E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& the_key) const {
  pairNode<K, E>* currentNode = firstNode;
  //  找到Key为the_key的键值对
  while (currentNode != NULL && currentNode->element.first != the_key)
    currentNode = currentNode->next;

  if (currentNode != NULL && currentNode->element.first == the_key)
    return &(currentNode->element);

  return NULL;
};

// 拆入键值对
template <typename K, typename E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& the_pair) {
  pairNode<K, E>* p = firstNode;
  pairNode<K, E>* tp = NULL;  // p的前驱节点

  // 顺醋查找键值对
  while (p != NULL && p->element.first < the_pair.first) {
    tp = p;
    p = p->next;
  }

  // 如果该key已经存在那么更新其value值
  if (p != NULL && p->element.first == the_pair.first) {
    p->element.second = the_pair.second;
    return;
  }

  // 如果key不存在，则插入
  pairNode<K, E>* newNode = new pairNode<K, E>(the_pair, p);
  if (tp == NULL)
    firstNode = newNode;
  else
    tp->next = newNode;

  // 处理size
  ++dSize;
  return;
};

// 删除键值对
template <typename K, typename E>
void sortedChain<K, E>::erase(const K& the_key) {
  pairNode<K, E>* p = firstNode;  // 需要删除的节点
  pairNode<K, E>* tp = NULL;      // P的前驱

  // 按key值搜寻节点
  while (p != NULL && p->element.first != the_key) {
    tp = p;
    p = p->next;
  }

  // 如果找到了
  if (p != NULL && p->element.first == the_key) {
    if (tp == NULL) {       // 如果要删除的是表头节点
      firstNode = p->next;  // 更新firstNode
    } else {
      tp->next = p->next;
    }
    delete p;
    dSize--;
  }

  //如果没找到则不用处理
};

// output
template <typename K, typename E>
void sortedChain<K, E>::output(std::ostream& out) const {
  // 循环输出
  for (pairNode<K, E>* p = firstNode; p != NULL; p = p->next) {
    out << "<"<<p->element.first << " " << p->element.second << "> ";
  }
}

// 重载<<
template <typename K, typename E>
std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& x) {
  x.output(out);
  return out;
}