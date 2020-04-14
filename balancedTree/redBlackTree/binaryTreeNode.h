#pragma once
#include <iostream>

#include "arrayQueue.h"

template <typename T>
struct binaryTreeNode {
  static const bool RED = true;
  static const bool BLACK = false;
  T element;                      // 储存的元素
  binaryTreeNode<T>* leftChild;   // 左孩子
  binaryTreeNode<T>* rightChild;  // 右孩子
  bool color;                     // 红黑树节点的颜色
  binaryTreeNode() { leftChild = rightChild = NULL; };
  binaryTreeNode(const T& theElement) : element(theElement), color(BLACK) {
    leftChild = rightChild = NULL;
  };
  binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild,
                 binaryTreeNode<T>* theRightChild)
      : element(theElement), color(BLACK) {
    leftChild = theLeftChild;
    rightChild = theRightChild;
  };

  // 供RBTree使用的构造函数
  binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild,
                 binaryTreeNode<T>* theRightChild, bool theColor)
      : element(theElement), color(theColor) {
    leftChild = theLeftChild;
    rightChild = theRightChild;
  };
};

// 访问节点
template <typename T>
void a_visit(binaryTreeNode<T>* x) {
  // 访问节点 *x
  std::cout << x->element << " ";
}

// 前序遍历
template <typename T>
void preOrder(binaryTreeNode<T>* t) {
  // 遍历二叉树 *t
  if (t != NULL) {
    a_visit(t);               // 访问
    preOrder(t->leftChild);   // 遍历左子树
    preOrder(t->rightChile);  // 遍历右子树
  }
};

//后续遍历
template <typename T>
void postOrder(binaryTreeNode<T>* t) {
  // 遍历二叉树t
  if (t != NULL) {
    postOrder(t->leftChild);   // 遍历左子树
    postOrder(t->rightChile);  // 遍历右子树
    a_visit(t);                // 访问
  }
};

// 中序遍历
template <typename E>
void inOrder(binaryTreeNode<E>* t) {
  if (t != NULL) {
    inOrder(t->leftChild);   // 遍历左子树
    a_visit(t);              // 访问
    inOrder(t->rightChile);  // 遍历右子树
  }
};

// 层次遍历
template <typename T>
void levelOrder(binaryTreeNode<T>* t) {
  // 层次遍历二叉树 *t
  arrayQueue<binaryTreeNode<T>*> q;  // 用一个队列来完成
  while (t != NULL) {
    a_visit(t);

    // 将t的孩子插入队列
    if (t->leftChild != NULL) {
      q.push(t->leftChild);
    }
    if (t->rightChile != NULL) {
      q.push(t->rightChile);
    }

    // 提取下一个要访问的节点
    try {
      t = q.front();
    } catch (queueEmpty) {
      std::cerr << "levelOrder finished" << std::endl;
      return;  // 如果队列空则证明遍历完毕
    }
    q.pop();
  }
};
