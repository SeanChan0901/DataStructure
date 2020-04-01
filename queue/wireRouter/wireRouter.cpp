// wireRouter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "arrayQueue.h"
#include "functionfOfArray.h"
#include "position.h"
using namespace std;


int **grid;  // 二维数组 用以标识网格，=1：被封锁  =0没被封锁且没有到达
             // >1表示一个位置
int wire_size;    // 方阵大小
int pathLength;          // 最短布线长度
arrayQueue<position> q;  // 当前位置
position start;          // 电路的一头
position finish;         // 电路的另一头
position *path;          // 最短布线的路径

void inputData() {  // Input the wire routing data.

  cout << "Enter grid size" << endl;
  cin >> wire_size;

  cout << "Enter the start position" << endl;
  cin >> start.row >> start.col;

  cout << "Enter the finish position" << endl;
  cin >> finish.row >> finish.col;

  // create and input the wiring grid array
  make2dArray(grid, wire_size + 2, wire_size + 2);
  cout << "Enter the wiring grid in row-major order" << endl;
  for (int i = 1; i <= wire_size; i++)
    for (int j = 1; j <= wire_size; j++) cin >> grid[i][j];
};

bool findPath() {
  // 寻找从开始点到终点的最短路径
  // 找到时返回true，否则返回false

  // 起点终点相同
  if ((start.row == finish.row) && (start.col == finish.col)) {
    pathLength = 0;
    return true;
  }

  // 初始化偏移量
  position offset[4];
  offset[0].row = 0;
  offset[0].col = 1;
  offset[1].row = 1;
  offset[1].col = 0;
  offset[2].row = 0;
  offset[2].col = -1;
  offset[3].row = -1;
  offset[3].col = 0;

  // 初始化网格周围的障碍物
  for (int i = 0; i <= wire_size + 1; i++) {
    grid[0][i] = grid[wire_size + 1][i] = 1;
    grid[i][0] = grid[i][wire_size + 1] = 1;
  }

  position here = start;
  grid[start.row][start.col] = 2;  // 采取一个增量2，2意思就是与开始点距离为0
  int numOfNbrs = 4;  // 一个方格的相邻位置数

  // 对于可达到的位置做标记
  arrayQueue<position> q;
  position nbr;

  // 访问该点的四个相邻位置
  // 给相邻的位置做标记
  do {
    for (int i = 0; i < numOfNbrs; i++) {
      nbr.row = here.row + offset[i].row;
      nbr.col = here.col + offset[i].col;
      if (grid[nbr.row][nbr.col] == 0) {                        // 未访问过
        grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;  // 访问这个位置
        // 并且记录距离
        if ((nbr.row == finish.row) &&
            (nbr.col == finish.col)) {  // 隔壁就是终点
          break;                        // 跳出循环
        }
        q.push(nbr);  // 否则把路径记录下来
      }
    }

    // 访问完该点的四相邻位置之后
    // 判断到底是到达终点跳出的for循环还是执行完所有的相邻点之后跳出的for循环
    // 到达终点的话跳出while
    if ((nbr.row == finish.row) && (nbr.col == finish.col)) break;

    // 没有到达终点
    if (q.empty()) {
      return false;  // 找寻路径失败
    }

    // 如果队列没空那么就一个一个找
    here = q.front();  // 下一个位置
    q.pop();
  } while (true);

  // 找到位置了
  // 构造路径
  pathLength = grid[finish.row][finish.col] - 2;
  path = new position[pathLength];

  // 从终点回溯
  here = finish;
  for (int j = pathLength - 1; j >= 0; j--) {
    path[j] = here;
    for (int i = 0; i < numOfNbrs; i++) {
      nbr.row = here.row + offset[i].row;
      nbr.col = here.col + offset[i].col;
      if (grid[nbr.row][nbr.col] == j + 2) break;  // ok路径正确，不需要再找邻点
    }
    here = nbr;
  }
  return true;
};

// output path to exit
void outputPath() {
  cout << "The wire path is" << endl;
  for (int i = 0; i < pathLength; i++)
    cout << path[i].row << " " << path[i].col << endl;
};

int main() {
  inputData();
  if (findPath())
    outputPath();
  else
    cout << "There is no wire path" << endl;

  return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
