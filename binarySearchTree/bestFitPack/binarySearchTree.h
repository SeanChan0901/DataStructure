#pragma once
#include <iostream>

#include "bsTree.h"
#include "linkedBinaryTree.h"

template <typename K, typename E>
class binarySearchTree : public bsTree<K, E>,
                         public linkedBinaryTree<std::pair<const K, E> > {
 public:
  bool empty() const { return this->treeSize == 0; };
  int size() const { return this->treeSize; }
  std::pair<const K, E>* find(const K& theKey) const;
  void insert(const std::pair<const K, E>& thePair);
  void erase(const K& theKey);

  // 升序
  void ascend() { this->inOrderOutput(); }  // 中序遍历就完事了
};

template <typename K, typename E>
std::pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const {
  // 返回指向对应关键字的数对的指针
  // 如果没有找到返回NULL
  binaryTreeNode<std::pair<const K, E> >* p = this->root;
  while (p != NULL) {
    if (theKey < p->element.first)  // 在左子树里面找
      p = p->leftChild;
    else if (theKey > p->element.first)  // 在右子树里面找
      p = p->rightChild;
    else  // 找到
      return &(p->element);
  }
  return NULL;  // 没有找到
};

template <typename K, typename E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair) {
  // 插入数对，重新组成二叉搜索树
  // 寻找位置插入
  binaryTreeNode<std::pair<const K, E> >* p = this->root;
  binaryTreeNode<std::pair<const K, E> >* pp = NULL;  // 插入位置的双亲

  while (p != NULL) {
    // 检查元素p->elelment
    pp = p;
    // 下移
    if (thePair.first < p->element.first)
      p = p->leftChild;
    else {
      if (thePair.first > p->element.first) p = p->rightChild;
      // 树中存在该关键字的数对，替换其值
      else {
        p->element.second = thePair.second;
        return;
      }
    }
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

// 二叉搜索树的删除
template <typename K, typename E>
void binarySearchTree<K, E>::erase(const K& theKey) {
  // 删除关键字等于theKey的数对
  // 查找关键字为theKey的节点
  binaryTreeNode<std::pair<const K, E> >* p = this->root;
  binaryTreeNode<std::pair<const K, E> >* pp = NULL;  // p的前驱
  while (p != NULL && p->element.first != theKey) {
    pp = p;
    if (theKey < p->element.first)
      p = p->leftChild;
    else
      p = p->rightChild;
  }
  if (p == NULL)  // 没有找到
    return;

  // 重新组织树的结构
  // p有两个孩子(策略选择用左孩子的最大值替换)
  if (p->leftChild != NULL && p->rightChild != NULL) {
    binaryTreeNode<std::pair<const K, E> >* smallestLeftChild = p->leftChild;
    binaryTreeNode<std::pair<const K, E> >* ps = p;  // 前驱
    while (smallestLeftChild != NULL) {  // 左子树里面找最大的
      ps = smallestLeftChild;
      smallestLeftChild = smallestLeftChild->rightChild;
    }

    // 将最大元素s移到p
    binaryTreeNode<std::pair<const K, E> >* q =
        new binaryTreeNode<std::pair<const K, E> >(smallestLeftChild->element,
                                                   p->leftChild, p->rightChild);
    if (pp == NULL)  // 如果删除的是根节点，则要更新此根节点
      this->root = q;

    else if (p == pp->leftChild) {
      pp->leftChild = q;
    } else
      pp->rightChild = q;

    // 找需要移动的节点（左子树最大节点）的前驱
    if (ps == p)  // 避免 p被删掉，这个节点会出错
      pp = q;
    else
      pp = ps;
    delete p;
    p = smallestLeftChild;
  }

  // p最多有一个孩子(左子树最大值)有一个左孩子
  // 把孩子存放在c
  binaryTreeNode<std::pair<const K, E> >* c;
  if (p->leftChild != NULL)
    c = p->leftChild;
  else
    c = p->rightChild;  // 如果上面的 p有两个孩子，这里c会==NULL

  // 删除p = smallestLeftChild;
  if (p == this->root)  // 如果p是根
    this->root = c;
  else {
    // p是pp的左孩子还是右孩子
    if (p == pp->leftChild)
      pp->leftChild = c;
    else
      pp->rightChild = c;
  }
  this->treeSize--;
  delete p;  // 删除smallestLeftChild
};
