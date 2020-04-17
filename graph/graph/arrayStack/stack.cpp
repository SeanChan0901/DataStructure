// stack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "arrayStack.h"
#include "printMatchPairs.h"  // 括号匹配：有全局变量
#include "towersOfHanoi.h"  // 汉诺塔问题：有全局变量，小心使用
#include "trackResort.h"   // 车厢重排：有全局变量
#include "checkBox.h"
using namespace std;

// 测试括号匹配
void testMatch() {
  string s;
  s="(3+5+(2-1/(1+1)))";
  printMatchPairs(s);
};

// 测试车厢重排
void railRoadResort() {
  // int p[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
  // cout << "Input permutation is 581742963" << endl;
  int p[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
  cout << "Input permutation is 369247185" << endl;
  railroad(p, 9, 3);
};

// 测试管脚布线
void testCheckBox() {
  int p[] = {1, 2, 2, 1,
             3, 3, 4, 4};  // 即值相等的两个元素是一个网组，其索引值代表管脚号
  checkBox(p, 8);
};

int main() {
  arrayStack<int> s;

  // add a few elements
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);

  cout << "Stack should be 1234, bottom to top" << endl;

  // test empty and size
  if (s.empty())
    cout << "The stack is empty" << endl;
  else
    cout << "The stack is not empty" << endl;

  cout << "The stack size is " << s.size() << endl;

  while (!s.empty()) {
    cout << "Stack top is " << s.top() << endl;
    s.pop();
    cout << "Popped top element" << endl;
  }

  try {
    s.pop();
  } catch (stackEmpty message) {
    cout << "Last pop failed " << endl;
    message.outputMessage();
  }

  // testMatch();
  towerOfHanoiWithRescursion(4, 1, 2, 3);
  towerOfHanoiWithStack(4, 1, 2, 3);
  // railRoadResort();
  // testCheckBox();

  return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5.
//   转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
