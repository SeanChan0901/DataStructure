#include <iostream>

#include "binarySearchTree.h"

template <typename K, typename E>
class AVLTree : public binarySearchTree<K, E> {
 public:
  // 用递归的方式重写了insert方法
  void insert(const std::pair<const K, E>& thePair) {
    insert(this->root, thePair);
  };
  void erase(const std::pair<const K, E>& thePair) {
    erase(this->root, thePair);
  };
  std::pair<const K, E>* find(const K& theKey) const {
    return find(this->root, theKey);
  };

 protected:
  //  递归插入
  static binaryTreeNode<std::pair<const K, E> >* insert(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      const std::pair<const K, E>& thePair);
  // 递归删除
  static binaryTreeNode<std::pair<const K, E> >* erase(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      const std::pair<const K, E>& thePair);
  // 递归查找
  static std::pair<const K, E>* find(binaryTreeNode<std::pair<const K, E> >* x,
                                     const K& theKey);
  // 查看该节点平衡因子
  static int balanceFactor(const binaryTreeNode<std::pair<const K, E> >* x) {
    return (AVLTree<K, E>::height(x->leftChild) -
            AVLTree<K, E>::height(x->rightChild));
  }
  // LL 旋转 返回旋转后的根节点
  static binaryTreeNode<std::pair<const K, E> >* LLRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // RR 旋转
  static binaryTreeNode<std::pair<const K, E> >* RRRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // LR 旋转
  static binaryTreeNode<std::pair<const K, E> >* LRRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // RL 旋转
  static binaryTreeNode<std::pair<const K, E> >* RLRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
};

// 插入递归算法
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::insert(
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
    // 插入节点后平衡被破坏
    if (balanceFactor(tree) == 2) {
      if (thePair.first < tree->leftChild->element.first)
        tree = LLRotation(tree);
      else
        tree = LRRotation(tree);
    }
  } else if (thePair.first > tree->element.first) {
    tree->rightChild = insert(tree->rightChild, thePair);
    if (balanceFactor(tree) == -2) {
      if (thePair.first > tree->rightChild->element.first)
        tree = RRRotation(tree);
      else
        tree = RLRotation(tree);
    }
  } else {
    // 如果key值相等，那么更新key值
    std::cout << "key " << thePair.first << " is already exist , insert failed!"
              << std::endl;
  }
  // 更新树高
  tree->height = (std::max(binarySearchTree<K, E>::height(tree->leftChild),
                           binarySearchTree<K, E>::height(tree->rightChild)) +
                  1);
  return tree;
};

// 删除递归算法
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::erase(
    binaryTreeNode<std::pair<const K, E> >*& tree,
    const std::pair<const K, E>& thePair){};

// 递归查找
template <typename K, typename E>
std::pair<const K, E>* AVLTree<K, E>::find(
    binaryTreeNode<std::pair<const K, E> >* x, const K& theKey) {
  if (x == NULL) return NULL;  // 查找失败
  if (x->element.first > theKey)
    return find(x->leftChild, theKey);
  else if (x->element.first < theKey)
    return find(x->rightChild, theKey);
  else
    return &(x->element);
};

// LL旋转
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::LLRotation(
    binaryTreeNode<std::pair<const K, E> >* lastBalancedNode) {
  binaryTreeNode<std::pair<const K, E> >* newBalancedNode;
  // LL旋转
  newBalancedNode = lastBalancedNode->leftChild;
  lastBalancedNode->leftChild = newBalancedNode->rightChild;
  newBalancedNode->rightChild = lastBalancedNode;

  // 更新高度
  lastBalancedNode->height =
      (std::max(AVLTree<K, E>::height(lastBalancedNode->leftChild),
                AVLTree<K, E>::height(lastBalancedNode->rightChild)) +
       1);
  newBalancedNode->height =
      (std::max(AVLTree<K, E>::height(newBalancedNode->leftChild),
                lastBalancedNode->height) +
       1);
  return newBalancedNode;
};

// RR旋转
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::RRRotation(
    binaryTreeNode<std::pair<const K, E> >* lastBalancedNode) {
  binaryTreeNode<std::pair<const K, E> >* newBalancedNode;
  // RR旋转
  newBalancedNode = lastBalancedNode->rightChild;
  lastBalancedNode->rightChild = newBalancedNode->leftChild;
  newBalancedNode->leftChild = lastBalancedNode;

  // 更新高度
  lastBalancedNode->height =
      (std::max(AVLTree<K, E>::height(lastBalancedNode->leftChild),
                AVLTree<K, E>::height(lastBalancedNode->rightChild)) +
       1);
  newBalancedNode->height =
      (std::max(AVLTree<K, E>::height(newBalancedNode->leftChild),
                lastBalancedNode->height) +
       1);
  return newBalancedNode;
};

// LR旋转
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::LRRotation(
    binaryTreeNode<std::pair<const K, E> >* lastBalancedNode) {
  lastBalancedNode->leftChild = RRRotation(lastBalancedNode->leftChild);
  return LLRotation(lastBalancedNode);
};

// RL旋转
// LR旋转
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::RLRotation(
    binaryTreeNode<std::pair<const K, E> >* lastBalancedNode) {
  lastBalancedNode->rightChild = LLRotation(lastBalancedNode->rightChild);
  return RRRotation(lastBalancedNode);
};