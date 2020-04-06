// arrayQueue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "arrayQueue.h"
using namespace std;

int main(){
  arrayQueue<int> q(4);

  // add a few elements
  q.push(1);
  cout << "Queue rear is " << q.back() << endl;
  q.push(2);
  cout << "Queue rear is " << q.back() << endl;
  q.push(3);
  cout << "Queue rear is " << q.back() << endl;
  q.push(4);
  cout << "Queue rear is " << q.back() << endl;

  cout << "Queue should be 1234, front to rear" << endl << endl << endl;

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
    cout << endl << endl << endl;
  }

  // create a wraparound queue and do array doubling
  arrayQueue<int> r(4);
  r.push(1);
  r.push(2);
  r.push(3);
  r.pop();
  r.pop();
  r.push(4);
  r.push(5);
  r.push(6);
  r.push(7);

  cout << "Queue should be 34567, front to rear" << endl << endl << endl;

  // test empty and size
  if (r.empty())
    cout << "The queue is empty" << endl;
  else
    cout << "The queue is not empty" << endl;

  cout << "The queue size is " << r.size() << endl;

  while (!r.empty()) {
    cout << "Queue front is " << r.front() << endl;
    r.pop();
    cout << "Popped front element" << endl;
  }

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
