// maze.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "arrayStack.h"
using namespace std;

// 迷宫位置
struct position {
  int col;  // 纵坐标
  int row;  // 行坐标
};

int size_of_maze;  // 迷宫大小（假定迷宫为方形）
int **maze;

arrayStack<position> *path;

void inputMaze() {  // Input the maze.
  cout << "Enter maze size" << endl;
  cin >> size_of_maze;
  make2dArray(maze, size_of_maze + 2, size_of_maze + 2);
  cout << "Enter maze in row major order" << endl;
  for (int i = 1; i <= size_of_maze; i++)
    for (int j = 1; j <= size_of_maze; j++) cin >> maze[i][j];
};

// 寻找路径函数，寻找一条从（1，1）到出口(size,size)的路径
// 若找到返回true否则返回false
bool findPath() {
  path = new arrayStack<position>;

  // 初始化偏移量
  position offset[4];
  // 0代表右边相邻的位置，行坐标部变，纵坐标偏移量为1
  offset[0].row = 0;
  offset[0].col = 1;
  offset[1].row = 1;
  offset[1].col = 0;
  offset[2].row = 0;
  offset[2].col = -1;
  offset[3].row = -1;
  offset[3].col = 0;

  // 初始化迷宫的外围围墙
  for (int i = 0; i <= size_of_maze + 1; i++) {
    // 本来迷宫一行有size个格子，因为两边
    // 加了围墙所以变成size+2个格子（循环size+2次）
    maze[0][i] = maze[size_of_maze + 1][i] = 1;  // 上下边界
    maze[i][0] = maze[i][size_of_maze + 1] = 1;  // 左右边界
  }

  position here;            // 当前位置
  here.row = here.col = 1;  //(1,1)起点
  maze[1][1] = 1;           // 防止回到入口
  int option = 0;           // 下一步 (左右上下0，1，2，3)
  int lastOption = 3;       // 剩余选择

  // 寻找一条路径
  // 没有到达边界（没有到达出口）
  while (here.row != size_of_maze || here.col != size_of_maze) {
    int r, c;                       // 下一个位置
    while (option <= lastOption) {  // 看一下剩余选择有多少个是可行的
      r = here.row + offset[option].row;
      c = here.col + offset[option].col;  // 探索下一个位置
      if (maze[r][c] == 0) {  // 下一个位置是通路（没有障碍物）
        break;                // 跳出循环
      }
      option++;  // 该位置有障碍物，寻找下一个可用位置
    }
    // 相邻位置有通路
    if (option <= lastOption) {
      // 移动到该位置maze[r][c]
      path->push(here);
      here.row = r;
      here.col = c;
      maze[r][c] = 1;  // 设置1以防重复访问
      option = 0;
    } else {              // 相邻位置没有一步可走的
      if (path->empty())  // 如果栈空证明迷宫没有出路
        return false;
      position next = path->top();  // 返回到之前的位置
      path->pop();
    }
  }
  return true;  // 找到了
};

void outputPath() {  // 原路返回，逆向输出(从出口到入口)
  cout << "The path is" << endl;
  position here;
  while (!path->empty()) {
    here = path->top();
    path->pop();
    cout << here.row << ' ' << here.col << endl;
  }
};

int main() {
  inputMaze();
  if (findPath())
    outputPath();
  else
    cout << "No path" << endl;
};

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
