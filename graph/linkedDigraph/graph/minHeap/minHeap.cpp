#include <iostream>
#include "minHeap.h"
using namespace std;
int main() {
  // test initialize
  int *completeBinaryTree = new int[7];
  completeBinaryTree[1] = 2;
  completeBinaryTree[2] = 10;
  completeBinaryTree[3] = 14;
  completeBinaryTree[4] = 15;
  completeBinaryTree[5] = 21;
  completeBinaryTree[6] = 20;
  minHeap<int> aMinHeap;
  for (int i = 1; i <= 6; i++) {
    cout << "<" << completeBinaryTree[i] << "> ";
  }
  aMinHeap.initialize(completeBinaryTree, 6);
  cout << aMinHeap << endl;

  // test heapSort
  int a[6];
  a[1] = 20;
  a[2] = 12;
  a[3] = 35;
  a[4] = 15;
  a[5] = 10;
  heapSort(a, 5);
  for(int i=1;i<=5;i++){
    cout<<a[i]<<" ";
  }
  return 0;
}