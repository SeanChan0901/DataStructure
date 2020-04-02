#pragma once
#include <iostream>

template <typename K, typename E>
struct pairNode {
  typedef std::pair<const K, E> pairType;
  pairType element;      // 键值对
  pairNode<K, E>* next;  // next指针

  pairNode(const pairType& the_pair) : element(the_pair){};
  pairNode(const pairType& the_pair, pairNode<K, E>* the_next)
      : element(the_pair) {
    next = the_next;
  };
};
