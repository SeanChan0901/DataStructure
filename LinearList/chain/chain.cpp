// chain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "chain.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include "ChainNode.h"
#include "LinearList.h"
#include "extendedChain.h"
using namespace std;

void testReverse();
void testOperator();
void testLeftShift();
void testMeld();
void testMerge();
void testSplit();
void testCircularShift();

int main() {
  // test constructor
  LinearList<double> *x = new chain<double>;
  chain<int> y, z;

  // test size
  cout << "Initial size of x, y, and z = " << x->size() << ", " << y.size()
       << ", " << z.size() << endl;

  // test empty
  if (x->empty())
    cout << "x is empty" << endl;
  else
    cout << "x is not empty" << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;

  // test insert
  y.insert(0, 2);
  y.insert(1, 6);
  y.insert(0, 1);
  y.insert(2, 4);
  y.insert(3, 5);
  y.insert(2, 3);
  cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
  cout << "Size of y = " << y.size() << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;
  y.output(cout);
  cout << endl << "Testing overloaded <<" << endl;
  cout << y << endl;

  // test indexOf
  int index = y.indexOf(4);
  if (index < 0)
    cout << "4 not found" << endl;
  else
    cout << "The index of 4 is " << index << endl;
  index = y.indexOf(7);
  if (index < 0)
    cout << "7 not found" << endl;
  else
    cout << "The index of 7 is " << index << endl;

  // test get
  cout << "Element with index 0 is " << y.get(0) << endl;
  cout << "Element with index 3 is " << y.get(3) << endl;

  // test erase
  y.erase(1);
  cout << "Element 1 erased" << endl;
  cout << "The list is " << y << endl;
  y.erase(2);
  cout << "Element 2 erased" << endl;
  cout << "The list is " << y << endl;
  y.erase(0);
  cout << "Element 0 erased" << endl;
  cout << "The list is " << y << endl;

  cout << "Size of y = " << y.size() << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;

  try {
    y.insert(-3, 0);
  } catch (IllegalIndex e) {
    cout << "Illegal index exception" << endl;
    cout << "Insert index must be between 0 and list size" << endl;
    e.outputMessage();
  }

  // test copy constructor
  chain<int> w(y);
  y.erase(0);
  y.erase(0);
  cout << "w should be old y, new y has first 2 elements removed" << endl;
  cout << "w is " << w << endl;
  cout << "y is " << y << endl;

  // a few more inserts, just for fun
  y.insert(0, 4);
  y.insert(0, 5);
  y.insert(0, 6);
  y.insert(0, 7);
  cout << "y is " << y << endl;

  cout << "\n\n\n\n\n\n\n\ntest extendedChain" << endl;
  // create an extended chain
  extendedChain<int> kkk;
  kkk.insert(0, 2);
  kkk.insert(1, 6);
  kkk.insert(0, 1);
  kkk.insert(2, 4);
  kkk.insert(3, 5);
  kkk.insert(2, 3);
  cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
  cout << "Size of y = " << kkk.size() << endl;

  // test iterator
  cout << "Ouput using forward iterators pre and post ++" << endl;
  for (extendedChain<int>::iterator i = kkk.begin(); i != kkk.end(); i++)
    cout << *i << "  ";
  cout << endl;
  for (extendedChain<int>::iterator i = kkk.begin(); i != kkk.end(); ++i) {
    cout << *i << "  ";
    *i += 1;
  }
  cout << endl;

  cout << "Incremented by 1 list is " << kkk << endl;

  // try out an STL algorithm
  int sum = accumulate(kkk.begin(), kkk.end(), 0);
  cout << "The sum of the elements is " << sum << endl;

  // clear the chain and do a few appends
  kkk.clear();

  kkk.push_back(1);
  kkk.push_back(2);
  kkk.push_back(3);
  cout << "Appended 3 integers, list y should be 1 2 3" << endl;
  cout << "Size of y = " << kkk.size() << endl;
  cout << kkk << endl;

  kkk.insert(3, 4);
  kkk.insert(0, 0);
  cout << "List y should be 0 1 2 3 4" << endl;
  cout << "Size of y = " << kkk.size() << endl;
  cout << kkk << endl;

  kkk.erase(4);
  kkk.erase(0);
  kkk.push_back(6);
  cout << "List y should be 1 2 3 6" << endl;
  cout << "Size of y = " << kkk.size() << endl;
  cout << kkk << endl;

  // testOperator();

  // testReverse();

  // testLeftShift();

  // testMeld();

  // testMerge();

  // testSplit();

  testCircularShift();

  return 0;
};

// test operator
void testOperator() {
  cout << "\n\n\n\n\n\n";
  chain<int> y, z;
  // test insert
  y.insert(0, 2);
  y.insert(1, 6);
  y.insert(0, 1);
  y.insert(2, 4);
  y.insert(3, 5);
  y.insert(2, 3);
  cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
  cout << "Size of y = " << y.size() << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;
  y.output(cout);
  cout << endl << "Testing overloaded <<" << endl;
  cout << y << endl;

  // test []
  for (int i = 0; i < y.size(); i++) {
    cout << y[i] << endl;
  }

  // test == ， !=
  chain<int> w(y);
  cout << "w is " << w << endl;
  cout << "y is " << y << endl;
  cout << (w == y ? "w == y" : "w != y") << endl;

  z.insert(0, 2);
  z.insert(1, 6);
  z.insert(0, 1);
  z.insert(2, 4);
  z.insert(3, 5);
  cout << "z is " << z << endl;
  cout << "y is " << y << endl;
  cout << (z == y ? "z == y" : "z != y") << endl;
  z.insert(2, 3);
  cout << "z is " << z << endl;
  cout << "y is " << y << endl;
  cout << (z == y ? "z == y" : "z != y") << endl;
  z.insert(2, 3);
};

// testreverse
void testReverse() {
  cout << "\n\n\n\n\n\n";
  chain<int> y;
  // test insert
  y.insert(0, 2);
  y.insert(1, 6);
  y.insert(0, 1);
  y.insert(2, 4);
  y.insert(3, 5);
  y.insert(2, 3);
  cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
  cout << "Size of y = " << y.size() << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;
  y.output(cout);
  cout << endl << "Testing overloaded <<" << endl;
  cout << y << endl;

  // test reverse
  y.reverse();
  cout << "after reverse  list y should be 6 5 4 3 2 1 " << endl;
  cout << y << endl;
};

void testLeftShift() {
  cout << "\n\n\n\n\n\n";
  chain<int> y, z;
  // test insert
  y.insert(0, 2);
  y.insert(1, 6);
  y.insert(0, 1);
  y.insert(2, 4);
  y.insert(3, 5);
  y.insert(2, 3);
  cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
  cout << "y is " << y << endl;
  y.leftShift(2);
  cout << "y left shift 2, list y should be 3 4 5 6" << endl;
  cout << "y is " << y << endl;
  y.leftShift(10);
  cout << "y left shift 10, list y should be notthing in it" << endl;
  cout << "y is " << y << endl;
  if (y.empty())
    cout << "y is empty" << endl;
  else
    cout << "y is not empty" << endl;
};

void testMeld() {
  chain<int> y, z, k;
  // test insert
  y.insert(0, 1);
  y.insert(1, 3);
  y.insert(2, 5);
  y.insert(3, 7);
  y.insert(4, 9);

  k.insert(0, 1);
  k.insert(1, 3);
  k.insert(2, 5);
  k.insert(3, 7);
  k.insert(4, 9);

  z.insert(0, 2);
  z.insert(1, 4);
  z.insert(2, 6);
  z.insert(3, 8);
  z.insert(4, 10);
  z.insert(5, 12);
  z.insert(6, 14);
  z.insert(7, 16);
  cout << "y is " << y << endl;
  cout << "z is " << z << endl;
  cout << "k is " << k << endl;
  cout << "meld y and z to k" << endl;
  k.meld(y, z);
  cout << "y size is" << y.size() << "\ny is " << y << endl << endl;
  cout << "z size is" << z.size() << "\nz is " << z << endl << endl;
  cout << "k size is" << k.size() << "\nk is " << k << endl << endl;
};

void testMerge() {
  chain<int> y, z, k;
  y.insert(0, 1);
  y.insert(1, 3);
  y.insert(2, 5);
  y.insert(3, 7);
  y.insert(4, 9);

  k.insert(0, 1);
  k.insert(1, 3);
  k.insert(2, 5);
  k.insert(3, 7);
  k.insert(4, 9);

  z.insert(0, 2);
  z.insert(1, 4);
  z.insert(2, 6);
  z.insert(3, 8);
  z.insert(4, 10);
  z.insert(5, 12);
  z.insert(6, 14);
  z.insert(7, 16);
  cout << "y is " << y << endl;
  cout << "z is " << z << endl;
  cout << "k is " << k << endl;
  cout << "merge y and z to k" << endl;
  k.merge(y, z);
  cout << "y size is" << y.size() << "\ny is " << y << endl << endl;
  cout << "z size is" << z.size() << "\nz is " << z << endl << endl;
  cout << "k size is" << k.size() << "\nk is " << k << endl << endl;
};

void testSplit() {
  chain<int> y, z, k;
  y.insert(0, 1);
  y.insert(1, 3);
  y.insert(2, 5);
  y.insert(3, 7);
  y.insert(4, 9);

  k.insert(0, 1);
  k.insert(1, 3);
  k.insert(2, 5);
  k.insert(3, 7);
  k.insert(4, 9);

  z.insert(0, 2);
  z.insert(1, 4);
  z.insert(2, 6);
  z.insert(3, 8);
  z.insert(4, 10);
  z.insert(5, 12);
  z.insert(6, 14);
  z.insert(7, 16);
  cout << "y is " << y << endl;
  cout << "z is " << z << endl;
  cout << "k is " << k << endl;
  cout << "split y to z and k" << endl;
  y.split(z, k);
  cout << "y size is" << y.size() << "\ny is " << y << endl << endl;
  cout << "z size is" << z.size() << "\nz is " << z << endl << endl;
  cout << "k size is" << k.size() << "\nk is " << k << endl << endl;
};

void testCircularShift() {
  chain<int> y;
  y.insert(0, 1);
  y.insert(1, 3);
  y.insert(2, 5);
  y.insert(3, 7);
  y.insert(4, 9);
  cout << "y is " << y << endl;
  cout << "y circular left move 11 " << endl;
  y.circularShift(11);
  cout << "y is " << y << endl;
};

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
