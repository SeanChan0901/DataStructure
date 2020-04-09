#include "huffmanTree.h"

#include <iostream>

#include "linkedBinaryTree.h"

int main() {

// test huffmanTree1
int a[11];
int n = 10;
for (int i = 1; i <= n; i++) a[i] = 2 * i;
linkedBinaryTree<int> *x = huffmanTree(a, n);
x->postOrderOutput();

  return 0;
}