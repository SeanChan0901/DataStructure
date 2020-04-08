#include "maxHeap.h"

#include <iostream>

using namespace std;
int main() {
  int *completeBinaryTree = new int[7];
  completeBinaryTree[1] = 2;
  completeBinaryTree[2] = 10;
  completeBinaryTree[3] = 14;
  completeBinaryTree[4] = 15;
  completeBinaryTree[5] = 21;
  completeBinaryTree[6] = 20;
  maxHeap<int> aMaxHeap;
  for(int i=1;i<=6;i++){
      cout<<"<"<<completeBinaryTree[i]<<"> ";
  }
  aMaxHeap.initialzie(completeBinaryTree,6);
  cout<<aMaxHeap<<endl;
  return 0;
}