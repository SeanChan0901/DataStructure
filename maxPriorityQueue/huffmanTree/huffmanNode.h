#pragma once
#include "linkedBinaryTree.h"

// 一个huffman节点里面保存一棵二叉树树
template <typename T>
struct huffmanNode {
  linkedBinaryTree<int>* tree;
  T weight;

  operator T() const { return weight; }
};