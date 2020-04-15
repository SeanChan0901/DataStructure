#include "redBlackTree.h"

#include <iostream>

#include "binarySearchTree.h"

using namespace std;
int main() {
  redBlackTree<int, char> a_bsTree;
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
  cout<<"\n\n\n\n";
  a_bsTree.deleteMax();
  a_bsTree.inOrderOutput();
  cout<<"\n\n\n\n";
  a_bsTree.erase(35);
  a_bsTree.inOrderOutput();
}