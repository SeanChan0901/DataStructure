// linkedQueue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "linkedQueue.h"
#include "myExceptions.h"
using namespace std;

int main() {
  linkedQueue<int> q;

  // add a few elements
  q.push(1);
  cout << "Queue back is " << q.back() << endl;
  q.push(2);
  cout << "Queue back is " << q.back() << endl;
  q.push(3);
  cout << "Queue back is " << q.back() << endl;
  q.push(4);
  cout << "Queue back is " << q.back() << endl;

  cout << "Queue should be 1234, front to back" << endl;

  // test empty and size
  if (q.empty())
    cout << "The queue is empty" << endl;
  else
    cout << "The queue is not empty" << endl;

  cout << "The queue size is " << q.size() << endl;

  while (!q.empty()) {
    cout << "Queue front is " << q.front() << endl;
    q.pop();
    cout << "Popped front element" << endl;
  }

  try {
    q.pop();
  } catch (queueEmpty message) {
    cout << "Last pop failed " << endl;
    message.outputMessage();
  }

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
