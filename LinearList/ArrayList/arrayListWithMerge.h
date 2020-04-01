#pragma once
#include <algorithm>
#include <numeric>
#include "ArrayList.h"

// 有序表
template <typename T>
class arrayListWithMerge : public ArrayList<T> {
 public:
  // 构造函数与ArrayList一样
  arrayListWithMerge(int initial_capacity = 10)
      : ArrayList<T>(initial_capacity){};
  ~arrayListWithMerge() {}

  // 合并
  void merge(const arrayListWithMerge<T>& a, const arrayListWithMerge<T>& b);
};

// 继承过来的protected为什么要用this指针来访问？
// 答：C++继承模板类，需要使用this指针或者Base::调用成员变量
// 在C++中如果父类是模板类，直接调用父类成员的话，会报错找不到该变量，其根本原因是因为模板的二次编译机制导致的。

//
template <typename T>
void arrayListWithMerge<T>::merge(const arrayListWithMerge<T>& a,
                                  const arrayListWithMerge<T>& b) {
  int cursor_a = 0;  // a表的游标
  int cursor_b = 0;  // b表的游标
  int cursor_c = 0;  // c表的游标

  // 在开始操作之前，先释放好已经分配的内存空间
  delete[] this->element;
  this->array_length = a.list_size + b.list_size;  // 成员函数可以访问私有成员
  this->element = new T[this->array_length];             // 分配新的内存空间

  // merge a和b
  while ((cursor_a < a.list_size) &&
         (cursor_b < b.list_size)) {  // 当两个表都还没复制完
    if (a.element[cursor_a] <= b.element[cursor_b]) {  // a表中的元素比b的小
      this->element[cursor_c++] =
          a.element[cursor_a++];  // a表中元素复制到新表，a和新表游标后移一位
    } else {                    // 如果b表中元素比a表中的小
      this->element[cursor_c++] =
          b.element[cursor_b++];  // b表中的元素复制到新表，b和新表游标后移一位
    }
  }  // 推出循环后至少又一个表元素已经复制完了（有可能两个表等长同时复制完）
  // 循环结束后，新表的游标cursor_c是最后一个元素的下一个位置
  // 把没有复制完的表的剩余的元素加到新表中
  std::copy(a.element + cursor_a, a.element + a.list_size, this->element + cursor_c);
  //  如果a复制到下标cursor_a时还没复制完，那么就从这里开始复制剩下的元素，
  //  如果已经复制完，此条那么不会复制任何东西
  //  复制的元素个数为 a.list_size-cursor_a
  cursor_c += (a.list_size - cursor_a);  // 此时cursor已经移到一个新的位置
  // （目前最后一个元素的下一个位置）准备下一次拷贝
  std::copy(b.element + cursor_b, b.element + b.list_size, this->element + cursor_c);
  cursor_c += (b.list_size - cursor_b);

  this->list_size = cursor_c;  // 刚好是list_size（目前最后一个元素的下一个位置）
};