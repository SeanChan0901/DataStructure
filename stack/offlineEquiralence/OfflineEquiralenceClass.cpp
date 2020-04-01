// OfflineEquiralenceClass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "arrayStack.h"
using namespace std;

int main() {
  int n;  // 元素个数
  int r;  // 关系个数
  cout << "Enter number of elements" << endl;
  cin >> n;
  if (n < 2) {
    cout << "Too few elements" << endl;
    return 1;  // 因错误而终止
  }
  cout << "Enter number of relations" << endl;
  cin >> r;
  if (r < 1) {
    cout << "Too few relations " << endl;
    return 1;
  }

  // 建立空栈组成的数组 stack[0]不用
  arrayStack<int>* list = new arrayStack<int>[n + 1];  // 储存关系的n张表

  // 输入r个关系，储存在表中
  int a, b;  // （a,b）是一个关系
  for (int i = 1; i <= r; i++) {
    cout << "Enter next relation/pair" << endl;
    cin >> a >> b;
    list[a].push(b);  // 更新关系表
    list[b].push(a);  // 更新关系表
  }

  // 初始化以输出等价类
  arrayStack<int> unprocessedList;
  bool* out = new bool[n + 1];
  for (int i = 1; i <= n; i++) {
    out[i] = false;  // 初始化，所有元素均未被输出
  }
  for (int i = 0; i <= n; i++) {
    if (!out[i]) {  // 如果这个元素未被输出过，启动一个新类
      cout << "Next class is: " << i << " ";
      out[i] = true;
      unprocessedList.push(i);
      // 从processedList 中取类剩余的元素
      while (!unprocessedList.empty()) {
        int j = unprocessedList.top();
        unprocessedList.pop();

        // 将表list[j]中的所有元素属于同一类
        while (!list[j].empty()) {
          int q = list[j].top();
          list[j].pop();
          if (!out[q]) {  // 如果q未输出，那么输出他
            cout << q << " ";
            out[q] = true;
            unprocessedList.push(q);
          }
        }
      }
      cout << endl;
    }
  }
  cout << "End of list of equivalence classes" << endl;
  return 0;
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
