#pragma once
#include <iostream>
#include "myExceptions.h"
#include "arrayStack.h"

// 将n个元素从塔x中移动到塔y中借助塔z,不借助栈
void towerOfHanoiWithRescursion(int n, int x, int y, int z) {
  if (n > 0) {
    towerOfHanoiWithRescursion(n - 1, x, z, y);  // 将n-1个碟从x移动到z借助y
    std::cout << "Move top disk "
              << "( the biggest disk in total " << n << " ) from tower " << x
              << "to tower " << y << std::endl;  // 把当前n中最大的碟从x放到y
    towerOfHanoiWithRescursion(n - 1, z, y,
                               x);  // 问题转化成将z中的n-1个盘子转到y中借助x
  }
};// 最后结果只显示移动方法并不显式每个时期塔一二三的布局

arrayStack<int> tower[4];  // 用来存储塔的布局


// 递归函数
void moveAndShow(int n, int x, int y, int z) {
  if (n > 0) {
    moveAndShow(n - 1, x, z, y);
    int d = tower[x].top();  // move a disk from top of
    tower[x].pop();          // tower x to top of
    tower[y].push(d);        // tower y
    // showState();              // show state of 3 towers
    // substitute showState code for test run
    std::cout << "Move disk " << d << " from tower " << x << " to top of tower "
              << y << std::endl;
    moveAndShow(n - 1, z, y, x);
  }
}

// 用栈来表示
void towerOfHanoiWithStack(int n, int x, int y, int z) {
  // 预处理
  for (int d = n; d > 0; d--) {
    tower[1].push(d);  // 从大到小依次入栈
  }
  moveAndShow(n, 1, 2, 3);
};