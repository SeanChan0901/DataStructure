#pragma once
#include <iostream>

#include "binarySearchTree.h"
#include "linkedBinaryTree.h"

template <typename K, typename E>
class redBlackTree : public binarySearchTree<K, E> {
 public:
  void insert(const std::pair<const K, E>& thePair) {
    insert(this->root, thePair);
    this->root->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
    this->treeSize++;
  };
  void erase(const K& theKey) {}

 protected:
  // 判断节点颜色
  static bool isRed(const binaryTreeNode<std::pair<const K, E> >* node);
  // 变换节点颜色
  static void flipColors(binaryTreeNode<std::pair<const K, E> >* node);

  // 向左旋转，返回旋转后的根节点 （跟AVL树的LL旋转不同）
  // 旋转tree节点的红色右链接
  static binaryTreeNode<std::pair<const K, E> >* rotateLeft(
      binaryTreeNode<std::pair<const K, E> >* tree);
  // 向右旋转，返回旋转后的根节点（跟AVL树的RR旋转不同）
  // 旋转tree节点的红色左链接
  static binaryTreeNode<std::pair<const K, E> >* rotateRight(
      binaryTreeNode<std::pair<const K, E> >* tree);
  static binaryTreeNode<std::pair<const K, E> >* insert(
      binaryTreeNode<std::pair<const K, E> >*&,
      const std::pair<const K, E>& thePair);
  static binaryTreeNode<std::pair<const K, E> >* erase(
      binaryTreeNode<std::pair<const K, E> >*&, const K& theKey);
};

template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::rotateLeft(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  binaryTreeNode<std::pair<const K, E> >* newTree = tree->rightChild;
  tree->rightChild = newTree->leftChild;
  newTree->leftChild = tree;
  newTree->color = tree->color;  // 保存原根节点的颜色
  tree->color =
      binaryTreeNode<std::pair<const K, E> >::RED;  // 原根结点改成红色
  return newTree;
};

template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::rotateRight(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  binaryTreeNode<std::pair<const K, E> >* newTree = tree->leftChild;
  tree->leftChild = newTree->rightChild;
  newTree->rightChild = tree;
  newTree->color = tree->color;  // 保存原根节点的颜色
  tree->color =
      binaryTreeNode<std::pair<const K, E> >::RED;  // 原根结点改成红色
  return newTree;
};

// 判断节点颜色
template <typename K, typename E>
bool redBlackTree<K, E>::isRed(
    const binaryTreeNode<std::pair<const K, E> >* node) {
  if (node == NULL)
    return binaryTreeNode<std::pair<const K, E> >::BLACK;  // 外部节点一律为黑色
  return node->color;
};

// 变换节点颜色
template <typename K, typename E>
void redBlackTree<K, E>::flipColors(
    binaryTreeNode<std::pair<const K, E> >* node) {
  node->color = binaryTreeNode<std::pair<const K, E> >::RED;
  node->leftChild->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
  node->rightChild->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
};

// 查找thePair，找到更新其值，找不到插入新的(插入的新节点默认是红节点)
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::insert(
    binaryTreeNode<std::pair<const K, E> >*& tree,
    const std::pair<const K, E>& thePair) {
  if (tree == NULL) {
    tree = new binaryTreeNode<std::pair<const K, E> >(
        std::pair<const K, E>(thePair), NULL, NULL,
        binaryTreeNode<std::pair<const K, E> >::RED);
    if (tree == NULL) throw IllegalParameterValue("new fail");
    return tree;
  } else if (thePair.first < tree->element.first) {
    tree->leftChild = insert(tree->leftChild, thePair);
  } else if (thePair.first > tree->element.first) {
    tree->rightChild = insert(tree->rightChild, thePair);
  } else {  // 找到，更新其值
    tree->element.second = thePair.second;
  }

  //  插入完成后进行调整 (是几次连续的独立调整，不能用else if)
  if (isRed(tree->rightChild) && (!isRed(tree->leftChild))) {
    tree = rotateLeft(tree);
  }
  if (isRed(tree->leftChild) && (isRed(tree->leftChild->leftChild))) {
    tree = rotateRight(tree);
  }
  if (isRed(tree->leftChild) && isRed(tree->rightChild)) {
    flipColors(tree);
  }

  return tree;
};