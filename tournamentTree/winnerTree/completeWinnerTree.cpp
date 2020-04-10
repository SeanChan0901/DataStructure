#include "completeWinnerTree.h"

#include <iostream>

using namespace std;

int main() {
  int playerList[9];
  playerList[1] = 4;
  playerList[2] = 6;
  playerList[3] = 5;
  playerList[4] = 9;
  playerList[5] = 8;
  playerList[6] = 2;
  playerList[7] = 3;
  playerList[8] = 7;
  completeWinnerTree<int> a_winnnerTree(playerList, 8);
  a_winnnerTree.output();
  cout<<"winner is "<<a_winnnerTree.winner();
  return 0;
};