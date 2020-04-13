#include "binarySearchTree.h"

#include <iostream>

#include "AVLTree.h"

using namespace std;

int main() {
  AVLTree<int, char> a_bsTree;
  a_bsTree.insert(pair<int, char>(2, 'a'));
  a_bsTree.insert(pair<int, char>(5, 'b'));
  a_bsTree.insert(pair<int, char>(30, 'c'));
  a_bsTree.insert(pair<int, char>(40, 'd'));
  a_bsTree.insert(pair<int, char>(35, 'e'));
  a_bsTree.insert(pair<int, char>(80, 'f'));
  a_bsTree.insert(pair<int, char>(85, 'g'));
  a_bsTree.insert(pair<int, char>(60, 'h'));
  a_bsTree.insert(pair<int, char>(32, 'i'));
  a_bsTree.insert(pair<int, char>(33, 'j'));
  a_bsTree.insert(pair<int, char>(31, 'k'));
  a_bsTree.insert(pair<int, char>(29, 'z'));

  a_bsTree.inOrderOutput();
  cout << "tree height is : " << a_bsTree.height()<<endl;
  cout<<"key "<<29<<" is "<<a_bsTree.find(29)->second;
  return 0;
};