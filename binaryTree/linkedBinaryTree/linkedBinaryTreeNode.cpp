#include <iostream>

#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
using namespace std;

int main() {
  // test 一棵算术表达式树
  binaryTreeNode<char>* leaves_1 = new binaryTreeNode<char>('a');
  binaryTreeNode<char>* leaves_2 = new binaryTreeNode<char>('b');
  binaryTreeNode<char>* leaves_3 = new binaryTreeNode<char>('c');
  binaryTreeNode<char>* leaves_4 = new binaryTreeNode<char>('d');
  binaryTreeNode<char>* node_1 =
      new binaryTreeNode<char>('*', leaves_1, leaves_2);
  binaryTreeNode<char>* node_2 =
      new binaryTreeNode<char>('/', leaves_3, leaves_4);
  binaryTreeNode<char>* root_1 = new binaryTreeNode<char>('+', node_1, node_2);
  // 前序遍历
  cout << "preOrder tree";
  preOrder(root_1);
  cout << endl;
  // 后续遍历
  cout << "postOrder tree";
  postOrder(root_1);
  cout << endl;

  // 中序遍历
  cout << "inOrder tree";
  inOrder(root_1);
  cout << endl;

  // 层次遍历
  cout << "levelOrder" << endl;
  levelOrder(root_1);
  cout << endl;

  // test linkedBinaryTree
  linkedBinaryTree<char> a_tree(root_1);
  a_tree.preOrderOutput();
  return 0;
};