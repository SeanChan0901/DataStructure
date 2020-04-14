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
  // 非递归查找
  std::pair<const K, E>* find(const K& theKey) const;
  // 递归查找
  binaryTreeNode<std::pair<const K, E> >* Rfind(const K& theKey) const {
    return find(this->root, theKey);
  };
  // 非递归插入
  void NRinsert(const std::pair<const K, E>& thePair);
  // 递归插入
  void insert(const std::pair<const K, E>& thePair) {
    insert(this->root, thePair);
    (this->treeSize)++;
  };
  // 非递归删除
  void NRerase(const K& theKey);
  // 递归删除
  void erase(const K& theKey) {
    erase(this->root, find(this->root, theKey));
    (this->treeSize)--;
  };

  // 升序
  void ascend() { this->inOrderOutput(); }  // 中序遍历就完事了
 protected:
  // 递归查找
  static binaryTreeNode<std::pair<const K, E> >* find(
      binaryTreeNode<std::pair<const K, E> >* x, const K& theKey);
  //  递归插入
  static binaryTreeNode<std::pair<const K, E> >* insert(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      const std::pair<const K, E>& thePair);
  // 递归删除
  static binaryTreeNode<std::pair<const K, E> >* erase(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      binaryTreeNode<std::pair<const K, E> >* deleteNode);
  // 查找以tree为根的最小节点 返回该节点
  static binaryTreeNode<std::pair<const K, E> >* minimum(
      binaryTreeNode<std::pair<const K, E> >* tree);
  // 查找以tree为根的最大节点 返回该节点
  static binaryTreeNode<std::pair<const K, E> >* maximum(
      binaryTreeNode<std::pair<const K, E> >* tree);
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
void binarySearchTree<K, E>::NRinsert(const std::pair<const K, E>& thePair) {
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
void binarySearchTree<K, E>::NRerase(const K& theKey) {
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

// 查找以tree为根的最小节点 返回该节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* binarySearchTree<K, E>::minimum(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (tree == NULL) return NULL;
  while (tree->leftChild != NULL) tree = tree->leftChild;
  return tree;
};

// 查找以tree为根的最大节点 返回该节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* binarySearchTree<K, E>::maximum(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (tree == NULL) return NULL;
  while (tree->rightChild != NULL) tree = tree->rightChild;
  return tree;
};

// 插入递归算法
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* binarySearchTree<K, E>::insert(
    binaryTreeNode<std::pair<const K, E> >*& tree,
    const std::pair<const K, E>& thePair) {
  // 空节点
  if (tree == NULL) {
    tree = new binaryTreeNode<std::pair<const K, E> >(
        std::pair<const K, E>(thePair));
    if (tree == NULL) throw IllegalParameterValue("new fail");
  } else if (thePair.first <
             tree->element.first) {  // 应该将其插入到tree的左子树
    tree->leftChild = insert(tree->leftChild, thePair);
  } else if (thePair.first > tree->element.first) {
    tree->rightChild = insert(tree->rightChild, thePair);
  } else {
    // 如果key值相等，更新value
    tree->element.second = thePair.second;
  }
  // 更新树高
  return tree;
};

// 递归查找
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* binarySearchTree<K, E>::find(
    binaryTreeNode<std::pair<const K, E> >* x, const K& theKey) {
  if (x == NULL) return NULL;  // 查找失败
  if (x->element.first > theKey)
    return find(x->leftChild, theKey);
  else if (x->element.first < theKey)
    return find(x->rightChild, theKey);
  else
    return x;
};

template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* binarySearchTree<K, E>::erase(
    binaryTreeNode<std::pair<const K, E> >*& tree,
    binaryTreeNode<std::pair<const K, E> >* deleteNode) {
  // 根为空，或者没有要删除的节点，直接返回NULL；
  if (tree == NULL || deleteNode == NULL) return NULL;
  if (deleteNode->element.first < tree->element.first) {
    // 要删除的节点在左子树
    tree->leftChild = erase(tree->leftChild, deleteNode);
  } else if (deleteNode->element.first > tree->element.first) {
    // 要删除的节点在右子树
    tree->rightChild = erase(tree->rightChild, deleteNode);
  } else {
    // tree是对应要删除的节点
    // tree左右孩子非空
    if ((tree->leftChild != NULL) && (tree->rightChild != NULL)) {
      binaryTreeNode<std::pair<const K, E> >* max =
          new binaryTreeNode<std::pair<const K, E> >(
              maximum(tree->leftChild)->element, tree->leftChild,
              tree->rightChild);
      tree = max;
      tree->leftChild = erase(tree->leftChild, max);
    } else {
      // 如果只有一个子树或者没有子树
      binaryTreeNode<std::pair<const K, E> >* temp = tree;
      tree = (tree->leftChild == NULL ? tree->rightChild : tree->leftChild);
      delete temp;
    }
  }
  return tree;
};