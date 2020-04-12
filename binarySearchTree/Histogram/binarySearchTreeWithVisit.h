#pragma once
#include <iostream>

#include "binarySearchTree.h"

// 用作访问函数
void add1(int& count) { count++; };

template <class K, class E>
class binarySearchTreeWithVisit : public binarySearchTree<K, E> {
 public:
  void insert(const std::pair<const K, E>&, void (*visit)(E& u));
};

template <class K, class E>
void binarySearchTreeWithVisit<K, E>::insert(
    const std::pair<const K, E>& thePair,
    void (*visit)(E& u)) {  // 如果thePair的关键字不存在那么插入他
                            // 如果存在则访问他

  // 寻找thePair.first
  binaryTreeNode<std::pair<const K, E> >*p = this->root,  // search pointer
      *pp = 0;                                            // parent of p
  while (p != NULL) {                                     // examine p->element
    pp = p;
    // 在子树中寻找
    if (thePair.first < p->element.first)
      p = p->leftChild;
    else if (thePair.first > p->element.first)
      p = p->rightChild;
    else {  // 如果存在则visit他
      visit(p->element.second);
      return;
    }
  }

  // 插入
  binaryTreeNode<std::pair<const K, E> >* newNode =
      new binaryTreeNode<std::pair<const K, E> >(thePair);
  if (this->root != NULL)  // 树不空
    if (thePair.first < pp->element.first)
      pp->leftChild = newNode;
    else
      pp->rightChild = newNode;
  else
    this->root = newNode;  // 插入空树
  this->treeSize++;
}