// ArrayList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "ArrayList.h"
#include <iostream>
#include "LinearList.h"
#include "VectorList.h"
#include "arrayListWithMerge.h"
#include "error.h"
#include "numeric"
using namespace std;

// test merge
void testMerge() {
  // test merge
  arrayListWithMerge<int> a_array;
  arrayListWithMerge<int> b_array;
  arrayListWithMerge<int> c_array;

  a_array.insert(0, 2);
  a_array.insert(1, 6);
  a_array.insert(0, 1);
  a_array.insert(2, 4);
  a_array.insert(3, 5);
  a_array.insert(2, 3);

  b_array.insert(0, 2);
  b_array.insert(1, 6);
  b_array.insert(0, 1);
  b_array.insert(2, 4);
  b_array.insert(3, 5);
  b_array.insert(2, 3);

  c_array.insert(0, 2);
  c_array.insert(1, 6);
  c_array.insert(0, 1);
  c_array.insert(2, 4);
  c_array.insert(3, 5);
  c_array.insert(2, 3);

  cout << "a_array : " << a_array << endl;
  cout << "b_array : " << b_array << endl;
  cout << "c_array : " << c_array << endl;

  c_array.merge(a_array, b_array);
  cout << "c_array after merge : " << c_array << endl;
}

// testMeld
void testMeld() {
  ArrayList<int> a_array;
  ArrayList<int> b_array;
  ArrayList<int> c_array;

  a_array.insert(0, 1);
  a_array.insert(1, 3);
  a_array.insert(2, 5);
  a_array.insert(3, 7);
  a_array.insert(4, 9);

  b_array.insert(0, 2);
  b_array.insert(1, 4);
  b_array.insert(2, 6);
  b_array.insert(3, 8);
  b_array.insert(4, 10);
  // b_array.insert(5, 12);  // 测试等长和不等长

  c_array.insert(0, 2);
  c_array.insert(1, 6);
  c_array.insert(0, 1);
  c_array.insert(2, 4);
  c_array.insert(3, 5);
  c_array.insert(2, 3);

  cout << "a_array : " << a_array << endl;
  cout << "b_array : " << b_array << endl;
  cout << "c_array : " << c_array << endl;

  c_array.meld(a_array, b_array);
  cout << "c_array after merge : " << c_array << endl;
}

// testSplit
void testSplit() {
  ArrayList<int> a_array;
  ArrayList<int> b_array;
  ArrayList<int> c_array;
  ArrayList<int> d_array;
  ArrayList<int> e_array;

  a_array.insert(0, 1);
  a_array.insert(1, 3);
  a_array.insert(2, 5);
  a_array.insert(3, 7);
  a_array.insert(4, 9);

  b_array.insert(0, 2);
  b_array.insert(1, 4);
  b_array.insert(2, 6);
  b_array.insert(3, 8);
  b_array.insert(4, 10);
  b_array.insert(5, 12);

  c_array.insert(0, 2);
  c_array.insert(1, 6);
  c_array.insert(0, 1);
  c_array.insert(2, 4);
  c_array.insert(3, 5);
  c_array.insert(2, 3);

  cout << "a_array : " << a_array << endl;
  cout << "b_array : " << b_array << endl;
  cout << "c_array : " << c_array << endl;

  c_array.meld(a_array, b_array);
  cout << "c_array after meld : " << c_array << endl;

  c_array.split(d_array, e_array);
  cout << "d_array : " << d_array << endl;
  cout << "e_array : " << e_array << endl;
};

// testReverse
void testReverse() {
  arrayListWithMerge<int> a_array;
  arrayListWithMerge<int> b_array;
  arrayListWithMerge<int> c_array;

  a_array.insert(0, 2);
  a_array.insert(1, 6);
  a_array.insert(0, 1);
  a_array.insert(2, 4);
  a_array.insert(3, 5);
  a_array.insert(2, 3);

  b_array.insert(0, 2);
  b_array.insert(1, 6);
  b_array.insert(0, 1);
  b_array.insert(2, 4);
  b_array.insert(3, 5);
  b_array.insert(2, 3);

  c_array.insert(0, 2);
  c_array.insert(1, 6);
  c_array.insert(0, 1);
  c_array.insert(2, 4);
  c_array.insert(3, 5);
  c_array.insert(2, 3);

  cout << "a_array : " << a_array << endl;
  cout << "b_array : " << b_array << endl;
  cout << "c_array : " << c_array << endl;

  c_array.merge(a_array, b_array);
  cout << "c_array after merge : " << c_array << endl;
  c_array.reverse();
  cout << "c_array after reverse : " << c_array << endl;
};

// Reverse
template <typename T>
void Reverse(ArrayList<T>& a_list) {
  a_list.reverse();
};

int main() {
  try {
    // test constructor
    LinearList<double>* x = new ArrayList<double>(20);
    // 注意这里不可写成new ArrayList<double>[20];
    // new ArrayList<double>(20)指的是创建一个指针x指向一个ArrayList类的对象，
    // 这个对象通过构造函数输入初始化值为（20）即一条容量为20的线性表
    // 而new ArrayList<double>[20]指的是创建一个ArrayList对象的数组，里面一共有
    // 20条线性表
    ArrayList<int> y(2), z;

    // test capacity
    cout << "Capacity of x, y and z = "
         << ((ArrayList<double>*)x)->capacity()  // 显式类型转换
         << ", " << y.capacity() << ", " << z.capacity() << endl;

    // test size
    cout << "Initial size of x, y and z = " << x->size() << ", " << y.size()
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
    if (z.empty())
      cout << "z is empty" << endl;
    else
      cout << "z is not empty" << endl;

    // test insert
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;  // 插入6个数长度为6
    cout << "Capacity of y = " << y.capacity()
         << endl;  // 倍增了两次的一维数组容量为8
    if (y.empty())
      cout << "y is empty" << endl;
    else
      cout << "y is not empty" << endl;  // y非空
    y.output(cout);
    cout << endl << "Testing overloaded <<" << endl;  // 重载运算符测试
    cout << y << endl << endl << endl;

    // test indexOf
    int index = y.indexOf(4);
    if (index < 0)
      cout << "4 not found" << endl;
    else
      cout << "the index of 4 is " << index << endl;

    index = y.indexOf(7);
    if (index < 0)
      cout << "7 not found" << endl;
    else
      cout << "The index of 7 is " << index << endl;

    // test get
    cout << "Element with index 0 is " << y.get(0) << endl;
    cout << "Element with index 3 is " << y.get(3) << endl;

    // test iterator
    cout << "before reverse,y: " << y << endl;
    std::reverse(y.begin(), y.end());
    cout << "after reverse y: " << y << endl;
    cout << "sum of the list 'y' : " << accumulate(y.begin(), y.end(), 0)
         << endl;

    // test erase
    y.erase(1);
    cout << "Element 1 erased" << endl;
    cout << "The list is " << y << endl;
    y.erase(2);
    cout << "Element 2 erased" << endl;
    cout << "The list is " << y << endl;

    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
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
    ArrayList<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;

    // test leftShitf
    cout << "w is 2 left shifted " << endl;
    w.leftShift(2);
    cout << "w is " << w << endl;

    // test Merge
    // testMerge();

    // testMeld
    // testMeld();

    // testSplit
    //testSplit();

    // testReverse
    // testReverse();

    /*
    // test VectorList
    // test constructor
    LinearList<double>* x = new VectorList<double>(20);
    VectorList<int> y(2), z;

    // test capacity
    cout << "Capacity of x, y and z = " << ((VectorList<double>*)x)->capacity()
         << ", " << y.capacity() << ", " << z.capacity() << endl;

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
    //
    注意vector中初始化的时候会给容器中的元素一个默认值的，所以y里面包含两个double类型的默认值
    y.insert(0, 2);  // 插入之后变成3个数字
    y.insert(1, 6);  // 四个
    y.insert(0, 1);  // 五个
    y.insert(2, 4);  // 六个
    y.insert(3, 5);  // 七个
    y.insert(2, 3);  // 八个
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
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

    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
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
    VectorList<int> w(y);
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

    // test iterator
    cout << "Ouput using forward iterators pre and post ++" << endl;
    for (VectorList<int>::iterator i = y.begin(); i != y.end(); i++)
      cout << *i << "  ";
    cout << endl;
    for (VectorList<int>::iterator i = y.begin(); i != y.end(); ++i)
      cout << *i << "  ";
    cout << endl;

    cout << "Ouput using backward iterators pre and post --" << endl;
    for (VectorList<int>::iterator i = y.end(); i != y.begin();
         cout << *(--i) << "  ")
      ;
    cout << endl;
    for (VectorList<int>::iterator i = y.end(); i != y.begin();) {
      i--;
      cout << *i << "  ";
      *i += 1;
    }
    cout << endl;
    cout << "Incremented by 1 list is " << y << endl;

    // try out some STL algorithms
    reverse(y.begin(), y.end());
    cout << "The reversed list is " << y << endl;
    int sum = accumulate(y.begin(), y.end(), 0);
    cout << "The sum of the elements is " << sum << endl;
    sort(y.begin(), y.end());
    cout << "The sorted list is " << y << endl;
    sort(y.begin(), y.end(), greater<int>());
    cout << "The list is descending order is " << y << endl
         << endl
         << endl
         << endl;

    vector<int>* a_vecotr = new vector<int>;
    cout << "capacity : " << a_vecotr->capacity() << endl
         << "size : " << a_vecotr->size() << endl;
    a_vecotr->reserve(10);
    cout << "capacity : " << a_vecotr->capacity() << endl
         << "size : " << a_vecotr->size() << endl;

    return 0;
    */

  } catch (const std::exception& e) {
    cerr << e.what() << endl;
  }
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
