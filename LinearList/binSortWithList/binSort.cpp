// binSort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "chain.h"
#include "studentRecord.h"
using namespace std;

int main() {
  studentRecord s;
  chain<studentRecord> c;
  for (int i = 1; i <= 20; i++) {
    s.score = i / 2;
    s.name = new string(s.score, 'a');  // 对这个分数，姓名命为分数个'a'
    c.insert(0, s);
  }
  // range为10 因为i/2的最大值为10
  cout << "The unsorted chain is" << endl;
  cout << "  " << c << endl;
  binSort(c, 10);
  cout << "The sorted chain is" << endl;
  cout << "  " << c << endl << endl << endl << endl;

  // 测试成员函数binSort
  studentRecord z;
  chain<studentRecord> k;
  for (int i = 1; i <= 20; i++) {
    z.score = i / 2;
    z.name = new string(z.score, 'a');  // 对这个分数，姓名命为分数个'a'
    k.insert(0, z);
  }
  // range为10 因为i/2的最大值为10
  cout << "The unsorted chain is" << endl;
  cout << "  " << k << endl;
  k.binSort(10);
  cout << "The sorted chain is" << endl;
  cout << "  " << k << endl;
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
