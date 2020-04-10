#pragma once
#include <iostream>

#include "myExceptions.h"
#include "winnerTree.h"

template <class T>
class completeWinnerTree : public winnerTree<T> {
 public:
  completeWinnerTree(T *thePlayer, int theNumberOfPlayers) {
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);
  };
  ~completeWinnerTree() { delete[] tree; };
  void initialize(T *, int);  // 初始化竞赛树
  int winner() const { return tree[1]; };
  int winner(int i)const{return (i<numberOfPlayers)?tree[i]:0;}  // 返回第i场比赛获胜者
  // 返回序号为i的比赛的胜利者
  int winner(int i) const { return (i < numberOfPlayers) ? tree[i] : 0; }
  void rePlay(int);
  void output() const;

 protected:
  int lowExt;  // 最底层外部节点的数量
  int offset;  // 与最底层内部节点同一层的最后一个节点序号
  int *tree;   // 赢者树
  int numberOfPlayers;       // 竞赛者数量
  T *player;                 // 竞赛者
  void play(int, int, int);  // 进行比赛
};

template <typename T>
void completeWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers) {
  // 对于竞赛者T[1:numberOfplayers]建立一棵赢者树
  // 并且进行第一轮比赛（在同一层从左到右）
  int n = theNumberOfPlayers;
  if (n < 2) throw IllegalParameterValue("numst have at least 2 players");

  player = thePlayer;
  numberOfPlayers = n;
  delete[] tree;
  tree = new int[n];

  // 寻找最底层外部节点
  int i, s;
  // s为最底层左边的外部节点
  for (s = 1; 2 * s <= n - 1; s += s)
    ;

  // 最底层内部节点个数为n-s;那么最底层外部节点的个数为2*(n-s)
  lowExt = 2 * (n - s);
  // 最底层内部节点的最右位置
  offset = 2 * s - 1;

  // 进行最底层的外部节点的比赛
  for (i = 2; i <= lowExt; i += 2)
    play((offset + i) / 2, i - 1, i);  // 进行比赛

  // 进行剩下的最底层的外部节点的比赛
  if (n % 2 == 1) {  // 如果竞赛者个数是奇数，那么不能刚好凑成一对比赛
    play(n / 2, tree[n - 1], lowExt + 1);  // 匹配好其比赛，一下跳过3个节点
    i = lowExt + 3;                        // 移到倒数第二层进行比赛
  } else
    i = lowExt + 2;  // 移到倒数第二层进行比赛

  // 倒数第二层比赛
  for (; i <= n; i += 2)
    play((i - lowExt + n - 1) / 2, i - 1, i);  // 完成剩余的比赛
};


template <typename T>
void completeWinnerTree<T>::play(int game, int leftChild, int rightChild) {
  // 进行tree[game]比赛，左右孩子比赛，储存胜利者
  tree[game] =
      (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;

  // 如果这场比赛作为右孩子（奇数场次），那么可以和他左边的兄弟再进行一场比赛
  while (game % 2 == 1 && game > 1) {
    tree[game / 2] =
        (player[tree[game - 1]] <= player[tree[game]] ? tree[game-1] : tree[game]);
    game /= 2;  // 移动到父母
  }
};

// 重赛
template <typename T>
void completeWinnerTree<T>::rePlay(int thePlayer) {
  int n = numberOfPlayers;
  if (thePlayer < 1 || thePlayer > n)
    throw IllegalParameterValue("Player index is illegal");

  int matchNode;   // 下一场要重赛的比赛
  int leftChild;   // matchNode的左孩子
  int rightChild;  // matchNode的右孩子

  // 找到第一场需要重赛的比赛和他的孩子
  if (thePlayer <= lowExt) {
    // 从最底层的比赛开始重赛
    matchNode = (offset + thePlayer) / 2;  // 找出双亲
    leftChild = 2 * matchNode - offset;    // 左竞赛者
    rightChild = leftChild + 1;            //右竞赛者

  } else {
    // 倒数第二层外部节点
    matchNode = (thePlayer - lowExt + n - 1) / 2;
    if (2 * matchNode ==
        n - 1) {  // 如果数奇数外部节点，thePlayer刚好是单下来的那个节点
      leftChild = tree[2 * matchNode];
      rightChild = thePlayer;
    } else {
      leftChild = 2 * matchNode - n + 1 + lowExt;  // 左竞赛者编号
      rightChild = leftChild + 1;
    }
  }

  // 重赛matchNode
  tree[matchNode] =
      (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;

  // 重赛第二场 如果是奇数场次
  if (matchNode == n - 1 && n % 2 == 1) {
    matchNode /= 2;  // 向上
    tree[matchNode] =
        (player[tree[n - 1]] <= player[lowExt + 1]) ? tree[n - 1] : lowExt + 1;
  }

  // 进行剩余的比赛
  matchNode /= 2;  // 向上
  for (; matchNode >= 1; matchNode /= 2) {
    tree[matchNode] =
        (player[tree[2 * matchNode]] <= player[tree[2 * matchNode + 1]])
            ? tree[2 * matchNode]
            : tree[2 * matchNode + 1];
  }
};

template <class T>
void completeWinnerTree<T>::output() const {
  std::cout << "number of players  = " << numberOfPlayers
            << " lowExt = " << lowExt << " offset = " << offset << std::endl;
  std::cout << "complete winner tree pointers are" << std::endl;
  for (int i = 1; i < numberOfPlayers; i++) std::cout << tree[i] << ' ';
  std::cout << std::endl;
};