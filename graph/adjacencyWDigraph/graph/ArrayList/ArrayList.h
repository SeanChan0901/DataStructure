#pragma once
#include <algorithm>
#include <iterator>
#include <sstream>  // 使用sstream都必须用这个
#include "LinearList.h"
#include "error.h"
#include "functionOfArray.h"
#include "myExceptions.h"

template <class T>
class ArrayList : public LinearList<T> {
 public:
  // 构造函数，复制构造函数和析构函数
  ArrayList(int initial_capacity = 10);  // 构造函数，输入数组长度默认初始化为10
  ArrayList(const ArrayList<T>&);  // 复制构造函数

  // 析构函数

  // 迭代器
  class iterator {
   public:
    // 用C++的typedef语句实现双向迭代器
    typedef std::bidirectional_iterator_tag
        iterator_category;  // 迭代器类型为双向
    typedef T value_type;   // 线性表对象种的元素的类型
    typedef std::ptrdiff_t difference_type;  // prrdiff_t用于指针之间作差运算的
    typedef T* pointer;    // 线性表对象的元素的指针
    typedef T& reference;  // 线性表对象的元素的引用
    iterator(T* the_psition = 0) { position = the_psition; };  // 初始化迭代器
    ~iterator(){};

    // 解引用操作符
    T& operator*() const {
      return *position;
    };  // *解引用操作符，返回指针指向的元素
    T* operator->() const {
      return &*position;
    };  // 一个指针p->f()实际上就是(*p).f()

    // 迭代器的值增加
    iterator& operator++() {  // 前置++：返回左值
      ++position;
      return *this;  // 前置++返回++之后的左值
    };
    iterator operator++(int) {  // 后置++：返回右值
      iterator old = *this;
      ++position;
      return old;  // 后置++返回++之前的右值
    };

    // 迭代器的值减少
    iterator& operator--() {  // 前置--：返回左值
      --position;
      return *this;
    };
    iterator operator--(int) {  // 后置--：返回右值
      iterator old = *this;
      --position;
      return old;
    };

    // ！=和==
    bool operator!=(const iterator& right) const {
      return position !=
             right.position;  // 指针的值可用纸判断是否指向同一个地址
    };
    bool operator==(const iterator& right) const {
      return position == right.position;
    };

   protected:
    T* position;
  };

  // ADT方法
  bool empty() const { return list_size == 0; };  // 判断线性表是否为空
  int size() const { return list_size; };         // 线性表元素个数
  T& get(int the_index) const;              // 获取索引为the_index的元素
  int indexOf(const T& the_element) const;  // 获取element第一次出现的索引
  void erase(int the_index);                // 删除
  void insert(int the_index, const T& the_element);  // 插入
  void output(std::ostream& out) const;              // 输出到流
  iterator begin() { return iterator(element); };  // 返回指向表首元素的指针
  iterator end() {
    return iterator(element + list_size);
  };  // 返回指向表末元素的后一个未知的指针

  // 其他方法
  int capacity() const { return array_length; };  // 数组容量

  // meld交替包含List a和b的元素
  void meld(const ArrayList<T>& a, const ArrayList<T>& b);

  // split 生成两个线性表a和b，a包含*this中索引为偶数的元素，b包含剩余的元素
  void split(ArrayList<T>& a, ArrayList<T>& b);

  // reserve 颠倒本表的顺序
  void reverse();

  // leftshift 整个数组向左移动i个位置
  void leftShift(int leftShiftCount);

 protected:
  void checkIndex(int the_index) const;  // 查看索引是否合法，若不合法则抛出异常
  T* element;                            // 储存线性表元素的一维数组
  int array_length;                      // 一维数组的容量
  int list_size;                         // 线性表中的元素个数
};

//构造函数
template <class T>
ArrayList<T>::ArrayList(int initial_capacity) {
  // 判断参数是否合法
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "Initial capacity = " << initial_capacity << "Must be > 0 ";
    throw IllegalParameterValue(s.str());
  }
  array_length = initial_capacity;
  element = new T[array_length];
  list_size = 0;
};

// 复制构造函数
template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& the_list) {
  array_length = the_list.array_length;  // 先复制capacity
  list_size = the_list.list_size;        // 复制size
  element = new T[array_length];
  std::copy(the_list.element, the_list.element + list_size,
            element);  // 复制element
};

// 查看索引函数
template <class T>
void ArrayList<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// 获取索引为the_index的元素
template <class T>
T& ArrayList<T>::get(int the_index) const {
  checkIndex(the_index);
  return element[the_index];
};

// 查找元素第一次出现的索引
template <class T>
int ArrayList<T>::indexOf(const T& the_element) const {
  int the_index = (int)(std::find(element, element + list_size, the_element) -
                        element);  // stl中的find函数
  if (the_index == list_size)
    return -1;  // 没找到返回-1
  else
    return the_index;
};

// 删除
template <class T>
void ArrayList<T>::erase(int the_index) {
  checkIndex(the_index);
  std::copy(element + the_index + 1, element + list_size, element + the_index);
  element[--list_size]
      .~T();  // --list_size让长度减一，并且对最后一个元素调用析构函数
};

// 插入
template <class T>
void ArrayList<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 ||
      the_index >
          list_size) {  // 顺序表是有序的最后一个插入位置索引应该是list_size，如果大于List_size则插入失败
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }

  // 判断是否还有空间插入
  if (list_size == array_length) {
    ChangeLength1D(element, array_length, 2 * array_length);
    array_length *= 2;  // 数组倍增
  }

  //移动元素 使用copy_backward:从右边开始拷贝
  std::copy_backward(element + the_index, element + list_size,
                     element + list_size + 1);
  element[the_index] = the_element;
  list_size++;
};

// 把一个线性表输出到流
template <class T>
void ArrayList<T>::output(std::ostream& out) const {
  std::copy(element, element + list_size, std::ostream_iterator<T>(out, " "));
};

// 重载<<
template <class T>
std::ostream& operator<<(std::ostream& out, const ArrayList<T>& x) {
  x.output(out);
  return out;
};

// meld
template <typename T>
void ArrayList<T>::meld(const ArrayList<T>& a, const ArrayList<T>& b) {
  // 游标
  int cursor_a = 0;
  int cursor_b = 0;
  int cursor_c = 0;

  array_length = a.list_size + b.list_size;  // 数组长度
  delete[] element;                          // 清除本表
  element = new T[array_length];             // 开辟新空间

  while ((cursor_a < a.list_size) && (cursor_b < b.list_size)) {
    if (cursor_a == cursor_b) {                     // 交叉复制
      element[cursor_c++] = a.element[cursor_a++];  // 拷贝a中元素
    } else {
      element[cursor_c++] = b.element[cursor_b++];  // 拷贝b中元素
    }
  }

  // 跳出循环后证明有一个已经包含完了,不知道哪个包含完了，反正都copy就完事了
  // 这样做的话还保证了如果a和b长度一样的话跳出循环的时候b是还有一个元素没有复制完的在下面也复制好
  std::copy(a.element + cursor_a, a.element + a.list_size, element + cursor_c);
  cursor_c += (a.list_size - cursor_a);  // 表末尾的下一个位置（下标）
  std::copy(b.element + cursor_b, b.element + b.list_size, element + cursor_c);
  cursor_c += (b.list_size - cursor_b);  // 表末的下一个位置（下标）
  list_size = cursor_c;

  /*

  // 不用std的话可以用下面的判断语句
  if (cursor_a ==
      a.list_size)  // 如果a先完，有两种情况，1）a和b同长度b还有一个没有copy完
                    // 2）b比a长。两种情况都只copy b就完事了
  {
    std::copy(b.element + cursor_b, b.element + b.list_size,
              element + cursor_c);  // 拷贝
    cursor_c += (b.list_size - cursor_b);
    list_size = cursor_c;
    return;
  }
  // a没复制完，b已经完了
  std::copy(a.element + cursor_a, a.element + a.list_size, element + cursor_c);
  cursor_c += (a.list_size - cursor_a);
  list_size = cursor_c;
  return;
  

  */
};

template <typename T>  // a是偶，b是奇
void ArrayList<T>::split(ArrayList<T>& a, ArrayList<T>& b) {
  // 首先要确定a和b的数组长度
  // 如果list_size%2!=0 啧证明有奇数个元素，最后一个元素下标为偶数
  delete[] a.element;  // 清空数组
  delete[] b.element;  // 清空数组
  b.array_length =
      (int)list_size /
      2;  // 奇数数组长度，向下取整，无论list_size是奇数还是偶数都是这样
  a.array_length = list_size - b.array_length;  // 偶数数组长度
  a.element = new T[a.array_length];
  b.element = new T[b.array_length];

  // 游标
  int cursor_a = 0;
  int cursor_b = 0;
  int cursor_c = 0;
  while ((cursor_a < a.array_length) && (cursor_b < b.array_length)) {
    if (cursor_c % 2 == 0) {  // 偶数下标
      a.element[cursor_a++] = element[cursor_c++];
    } else {  // 奇数下标
      b.element[cursor_b++] = element[cursor_c++];
    }
  }
  // b满或者a满
  if (cursor_a == a.array_length) {  // a满，把b剩下的那一个放进去
    b.element[cursor_b] = element[cursor_c];
  } else {
    // b满，把a剩下的放进去
    a.element[cursor_a] = element[cursor_c];
  }
  a.list_size = a.array_length;
  b.list_size = b.array_length;
};

// reverse
template<typename T>
void ArrayList<T>::reverse() {
  T temp_element;                              // 临时用于交换的变量
  for (int i = 0; i < (list_size / 2); i++) {  // 交换次数为list_size/2
    temp_element = element[i];
    element[i] = element[list_size - i - 1];  // 交换
    element[list_size - i - 1] = temp_element;
  }
};

// leftShift
template <typename T>
void ArrayList<T>::leftShift(int leftShiftCount) {
  // 判断是否能移动i个位置
  if (leftShiftCount <= 0) return;  // 如果小于等于零，不管
  int newSize = 0;
  if (leftShiftCount < list_size) {        // 如果不用全部移掉
    newSize = list_size - leftShiftCount;  // 新的长度
    std::copy(element + leftShiftCount, element + list_size, element);  // 移动
  }
  for (int i = newSize; i < list_size; i++) {  // 析构
    element[i].~T();
  }
  // 从右删更容易理解把
  /*
  for (int i = (list_size - 1); i >= (newSize - 1); i--) {
    element[i].~T();
  }
  */
  list_size = newSize;
};