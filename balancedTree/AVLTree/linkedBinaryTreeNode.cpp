#include <iostream>

#include "binaryTreeNode.h"
#include "linkedBinaryTree.h"
using namespace std;

int main() {
  // test 一棵算术表达式树
  linkedBinaryTree<char> emptyTree;
  linkedBinaryTree<char> a_binaryTree;
  linkedBinaryTree<char> b_binaryTree;
  linkedBinaryTree<char> c_binaryTree;
  linkedBinaryTree<char> d_binaryTree;
  linkedBinaryTree<char> e_binaryTree;
  linkedBinaryTree<char> f_binaryTree;
  linkedBinaryTree<char> g_binaryTree;
  a_binaryTree.makeTree('a', emptyTree, emptyTree);
  b_binaryTree.makeTree('b', emptyTree, emptyTree);
  c_binaryTree.makeTree('c', emptyTree, emptyTree);
  d_binaryTree.makeTree('d', emptyTree, emptyTree);
  e_binaryTree.makeTree('*', a_binaryTree, b_binaryTree);
  f_binaryTree.makeTree('/', c_binaryTree, d_binaryTree);
  g_binaryTree.makeTree('+', e_binaryTree, f_binaryTree);

  cout << "tree height is " << g_binaryTree.height() << endl;
  g_binaryTree.preOrderOutput();
  g_binaryTree.inOrderOutput();
  g_binaryTree.postOrderOutput();
  return 0;
};