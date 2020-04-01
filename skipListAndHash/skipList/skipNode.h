#pragma once
#include <iostream>

// 跳表节点
// next[i]表示i级链表指针
// 对于一个lev级链表数对，其size值应该为lev+1
template <typename K, typename E>
struct skipNode {
  typedef std::pair<const K, E> pairType;
  pairType element;  // 键值对
  skipNode<K, E>** next;  // 指针数组,每个节点都要有一个大于自身级数的指针域
  skipNode(const pairType& the_pair, int size) : element(the_pair) {
    if (size == 0)
      next = NULL;  // 如果size==0（tailNode）其next域名为0
    else
      next = new skipNode<K, E>*[size];  // 指针数组，用于每一级链表
  }
};