#include <iostream>

#include "binarySearchTree.h"
template <typename K, typename E>
class AVLTree : public binarySearchTree<K, E> {
 public:
  // 用递归的方式重写了insert方法
  void insert(const std::pair<const K, E>& thePair) {
    insert(this->root, thePair);
  };
  void erase(const K& theKey) {
    binaryTreeNode<std::pair<const K, E> >* z = find(this->root, theKey);
    if (z != NULL)  // 如果有这个节点存在
      erase(this->root, z);
  };
  std::pair<const K, E>* find(const K& theKey) const {
    return &(find(this->root, theKey)->element);
  };

 protected:
  //  递归插入
  static binaryTreeNode<std::pair<const K, E> >* insert(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      const std::pair<const K, E>& thePair);
  // 递归删除
  static binaryTreeNode<std::pair<const K, E> >* erase(
      binaryTreeNode<std::pair<const K, E> >*& tree,
      binaryTreeNode<std::pair<const K, E> >*);
  // 递归查找
  static binaryTreeNode<std::pair<const K, E> >* find(
      binaryTreeNode<std::pair<const K, E> >* x, const K& theKey);
  // 查看该节点平衡因子
  static int balanceFactor(const binaryTreeNode<std::pair<const K, E> >* x) {
    return (AVLTree<K, E>::height(x->leftChild) -
            AVLTree<K, E>::height(x->rightChild));
  }
  // LL 旋转 返回旋转后的根节点
  static binaryTreeNode<std::pair<const K, E> >* LLRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // RR 旋转 返回旋转后的根节点
  static binaryTreeNode<std::pair<const K, E> >* RRRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // LR 旋转 返回旋转后的根节点
  static binaryTreeNode<std::pair<const K, E> >* LRRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // RL 旋转 返回旋转后的根节点
  static binaryTreeNode<std::pair<const K, E> >* RLRotation(
      binaryTreeNode<std::pair<const K, E> >* lastBalancedNode);
  // 查找以tree为根的最小节点 返回该节点
  static binaryTreeNode<std::pair<const K, E> >* minimum(
      binaryTreeNode<std::pair<const K, E> >* tree);
  // 查找以tree为根的最大节点 返回该节点
  static binaryTreeNode<std::pair<const K, E> >* maximum(
      binaryTreeNode<std::pair<const K, E> >* tree);
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
    // 如果key值相等，插入失败
    std::cout << "key " << thePair.first << " is already exist , insert failed!"
              << std::endl;
  }
  // 更新树高
  tree->height = (std::max(binarySearchTree<K, E>::height(tree->leftChild),
                           binarySearchTree<K, E>::height(tree->rightChild)) +
                  1);
  return tree;
};

// 递归查找
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::find(
    binaryTreeNode<std::pair<const K, E> >* x, const K& theKey) {
  if (x == NULL) return NULL;  // 查找失败
  if (x->element.first > theKey)
    return find(x->leftChild, theKey);
  else if (x->element.first < theKey)
    return find(x->rightChild, theKey);
  else
    return x;
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

// 查找以tree为根的最小节点 返回该节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::minimum(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (tree == NULL) return NULL;
  while (tree->leftChild != NULL) tree = tree->leftChild;
  return tree;
};

// 查找以tree为根的最大节点 返回该节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::maximum(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (tree == NULL) return NULL;
  while (tree->rightChild != NULL) tree = tree->rightChild;
  return tree;
};

template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* AVLTree<K, E>::erase(
    binaryTreeNode<std::pair<const K, E> >*& tree,
    binaryTreeNode<std::pair<const K, E> >* z) {
  // 根为空，或者没有要删除的节点，直接返回NULL；
  if (tree == NULL || z == NULL) return NULL;
  if (z->element.first < tree->element.first) {
    // 要删除的节点在左子树
    tree->leftChild = erase(tree->leftChild, z);
    // 若删除之后，AVL树失衡，则进行相应的旋转
    if (balanceFactor(tree) == (-2)) {
      // 进行L旋转
      binaryTreeNode<std::pair<const K, E> >* r = tree->rightChild;
      if (balanceFactor(r) == 1)
        tree = RLRotation(tree);
      else
        tree = RRRotation(tree);
    }
  } else if (z->element.first > tree->element.first) {
    // 要删除的节点在右子树
    tree->rightChild = erase(tree->rightChild, z);
    // 若删除之后，AVL树失衡，则进行相应的旋转
    if (balanceFactor(tree) == (2)) {
      // 进行L旋转
      binaryTreeNode<std::pair<const K, E> >* r = tree->leftChild;
      if (balanceFactor(r) == (-1))
        tree = LRRotation(tree);
      else
        tree = LLRotation(tree);
    }
  } else {
    // tree是对应要删除的节点
    // tree左右孩子非空
    if ((tree->leftChild != NULL) && (tree->rightChild != NULL)) {
      if (balanceFactor(tree) == 1) {
        // 如果tree的左子树比右子树高；
        // 则(01)找出tree的左子树中的最大节点
        //   (02)将该最大节点的值赋值给tree。
        //   (03)删除该最大节点。
        // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的
        binaryTreeNode<std::pair<const K, E> >* max =
            new binaryTreeNode<std::pair<const K, E> >(
                maximum(tree->leftChild)->element, tree->leftChild,
                tree->rightChild);
        tree = max;
        tree->leftChild = erase(tree->leftChild, max);
      } else {
        // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
        // 则(01)找出tree的右子树中的最小节点
        //   (02)将该最小节点的值赋值给tree。
        //   (03)删除该最小节点。
        // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
        binaryTreeNode<std::pair<const K, E> >* min =
            new binaryTreeNode<std::pair<const K, E> >(
                minimum(tree->rightChild)->element, tree->leftChild,
                tree->rightChild);
        tree = min;
        tree->rightChild = erase(tree->rightChild, min);
      }
    } else {
      // 如果只有一个子树或者没有子树
      binaryTreeNode<std::pair<const K, E> >* temp = tree;
      tree = (tree->leftChild == NULL ? tree->rightChild : tree->leftChild);
      delete temp;
    }
  }
  // 更新树高
  if(tree!=NULL){
    tree->height = (std::max(binarySearchTree<K, E>::height(tree->leftChild),
                           binarySearchTree<K, E>::height(tree->rightChild)) +
                  1);
  }
  return tree;
};