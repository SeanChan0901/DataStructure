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
  void erase(const K& theKey) {
    if (this->treeSize < 1) {
      std::cout << "empty tree" << std::endl;
      return;
    }
    if (!isRed(this->root->leftChild) && (!isRed(this->root->rightChild)))
      this->root->color = binaryTreeNode<std::pair<const K, E> >::RED;
    this->root = erase(this->root, theKey);
    if (this->root != NULL)
      this->root->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
    (this->treeSize)--;
  };
  void deleteMin();
  void deleteMax();

  void inOrderOutput() { this->inOrder(output); };

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
  // 平衡函数
  static binaryTreeNode<std::pair<const K, E> >* balance(
      binaryTreeNode<std::pair<const K, E> >*);
  // 左移红色节点
  static binaryTreeNode<std::pair<const K, E> >* moveRedLeft(
      binaryTreeNode<std::pair<const K, E> >*);
  // 右移红色节点
  static binaryTreeNode<std::pair<const K, E> >* moveRedRight(
      binaryTreeNode<std::pair<const K, E> >*);
  // deleteMin
  static binaryTreeNode<std::pair<const K, E> >* deleteMin(
      binaryTreeNode<std::pair<const K, E> >*);
  // deleteMax
  static binaryTreeNode<std::pair<const K, E> >* deleteMax(
      binaryTreeNode<std::pair<const K, E> >*);
  static void output(binaryTreeNode<std::pair<const K, E> >* t) {
    std::cout << t->element << " " << (isRed(t) ? "RED" : "BLACK") << std::endl;
  }
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
  node->color = !(node->color);
  node->leftChild->color = !(node->leftChild->color);
  node->rightChild->color = !(node->rightChild->color);
};

// 平衡函数
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::balance(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  //  插入完成后进行调整 (是几次连续的独立调整，不能用else if)
  if (isRed(tree->rightChild)) {
    // 由于删除了最左节点，所以不需要判断左是否为黑
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

template <typename K, typename E>
void redBlackTree<K, E>::deleteMin() {
  if (this->treeSize < 1) {
    std::cout << "tree empty" << std::endl;
    return;
  }
  if (!isRed(this->root->leftChild) && !(isRed(this->root->rightChild)))
    this->root->color = binaryTreeNode<std::pair<const K, E> >::RED;

  this->root = deleteMin(this->root);
  if (this->root != NULL)
    this->root->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
  this->treeSize--;
};

template <typename K, typename E>
void redBlackTree<K, E>::deleteMax() {
  if (this->treeSize < 1) {
    std::cout << "tree empty" << std::endl;
    return;
  }
  if (!isRed(this->root->leftChild) && !(isRed(this->root->rightChild)))
    this->root->color = binaryTreeNode<std::pair<const K, E> >::RED;

  this->root = deleteMax(this->root);
  if (this->root != NULL)
    this->root->color = binaryTreeNode<std::pair<const K, E> >::BLACK;
  this->treeSize--;
};

// 左边的将2-节点变为3-节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::moveRedLeft(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  // 假设tree为红，其左孩子以及左孩子的左孩子都是黑色（左孩子是2-节点）
  // 将tree左孩子或者tree左孩子的孩子变为红色（left变成2-节点）
  flipColors(tree);  // 颜色变换
  if (isRed(tree->rightChild->leftChild)) {
    // left的兄弟不是（2-节点），拿过来用一下
    tree->rightChild = rotateRight(tree->rightChild);
    tree = rotateLeft(tree);
  }
  return tree;
};

// 右边的将2-节点变为3-节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::moveRedRight(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  // 假设tree为红，其左孩子以及右孩子的左孩子都是黑色（右孩子是2-节点）
  // 将tree右孩子或者tree右孩子的孩子变为红色（right变成2-节点）
  flipColors(tree);  // 颜色变换
  if (!isRed(tree->leftChild->leftChild)) {
    // 左边右红色节点，而且左孩子的左孩子为黑色（左孩子是2-节点（把tree自己给他用）
    tree = rotateRight(tree);
  }
  return tree;
};

// 删除以tree为根的子树的最小节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::deleteMin(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (tree->leftChild == NULL) {
    // 因为已经将2-
    // 节点转化成3-节点或者4-节点了所以他不可能有右子树（红黑树定义）
    // 直接删除就好了
    delete tree;
    return NULL;
  }
  // 左孩子是2-节点,将其改成3-或者4-节点
  if (!isRed(tree->leftChild) && (!isRed(tree->leftChild->leftChild)))
    tree = moveRedLeft(tree);
  tree->leftChild = deleteMin(tree->leftChild);  // 递归删除最小节点
  return balance(tree);
};

// 删除以tree为根的子树的最小节点
template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::deleteMax(
    binaryTreeNode<std::pair<const K, E> >* tree) {
  if (isRed(tree->leftChild))
    tree = rotateRight(tree);  // 由于在定义时，红链接全为左链接，将其转过来
  if (tree->rightChild == NULL) {
    // 因为已经将2-
    // 节点转化成3-节点或者4-节点了所以他不可能有右子树（红黑树定义）
    // 直接删除就好了
    delete tree;
    return NULL;
  }
  // 左孩子是2-节点,将其改成3-或者4-节点
  if (!isRed(tree->rightChild) && (!isRed(tree->rightChild->leftChild)))
    tree = moveRedRight(tree);
  tree->rightChild = deleteMax(tree->rightChild);  // 递归删除最小节点
  return balance(tree);
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
    // return tree;
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

template <typename K, typename E>
binaryTreeNode<std::pair<const K, E> >* redBlackTree<K, E>::erase(
    binaryTreeNode<std::pair<const K, E> >*& tree, const K& theKey) {
  if (theKey < tree->element.first) {
    // 左边节点为2-节点的话，旋转使其成为3-或者4-节点
    if (!isRed(tree->leftChild) && (!isRed(tree->rightChild)))
      tree = moveRedLeft(tree);
    tree->leftChild = erase(tree->leftChild, theKey);
  } else if (theKey > tree->element.first) {
    if (isRed(tree->leftChild)) tree = rotateRight(tree);
    if (!isRed(tree->rightChild) && (!isRed(tree->rightChild->leftChild)))
      tree = moveRedRight(tree);
    tree->rightChild = erase(tree->rightChild, theKey);
  } else {  // 找到要删除的节点
    binaryTreeNode<std::pair<const K, E> >* min =
        redBlackTree<K, E>::minimum(tree->rightChild);
    binaryTreeNode<std::pair<const K, E> >* replaceNode =
        new binaryTreeNode<std::pair<const K, E> >(
            min->element, tree->leftChild, tree->rightChild, tree->color);
    tree = replaceNode;
    tree->rightChild = deleteMin(tree->rightChild);
  }
  return balance(tree);
};
