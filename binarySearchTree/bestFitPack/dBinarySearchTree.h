#include "binarySearchTree.h"

template <typename K, typename E>
class dBinarySearchTree : public binarySearchTree<K, E> {
 public:
  void insert(const std::pair<const K, E>&);
};

template <typename K, typename E>
void dBinarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair) {
  // 插入thePair，允许键值相同
  // 寻找位置插入
  binaryTreeNode<std::pair<const K, E> >* p = this->root;
  binaryTreeNode<std::pair<const K, E> >* pp = NULL;  // 插入位置的双亲

  while (p != NULL) {
    // 检查元素p->elelment
    pp = p;
    // 下移
    if (thePair.first <= p->element.first)
      p = p->leftChild;
    else
      p = p->rightChild;
  }

  // 新建一个节点插入
  binaryTreeNode<std::pair<const K, E> >* newNode =
      new binaryTreeNode<std::pair<const K, E> >(thePair);
  if (this->root != NULL)
    if (thePair.first < pp->element.first)
      pp->leftChild = newNode;
    else
      pp->rightChild = newNode;
  else
    this->root = newNode;
  (this->treeSize)++;
};