#ifndef functionOfArray_
#define functionOfArray_

#include <math.h>

#include <algorithm>
#include <iostream>

#include "myExceptions.h"

template <typename T>
void ChangeLength1D(T*& a, int old_length, int new_length) {
  if (new_length < 0) throw IllegalParameterValue("length must be > 0");
  T* temp = new T[new_length];                    // 新数组
  int number = std::min(old_length, new_length);  // 确认需要复制的元素个数
  std::copy(a, a + number, temp);  // 请查看迭代器中end()指向的到底是那个位置
  delete[] a;
  a = temp;
};  // 更改一维数组的长度

// 输入行数和列数创建一个二维数组
template <typename T>
bool make2dArray(T**& x, int numberOfRows,
                 int numberOfColumns) {  // 创建二维数组

  try {
    // 创建一维shuzu
    x = new T*[numberOfRows];

    // 为每行分配列数
    for (int i = 0; i < numberOfRows; i++) x[i] = new int[numberOfColumns];
    return true;
  } catch (std::bad_alloc) {
    return false;
  }
};

template <typename T>
bool delete2DArray(T**& x, int numberOfRows) {
  try {
    for (int i = 0; i < numberOfRows; i++) delete[] x[i];
    return true;
  } catch (std::bad_exception) {
    return false;
  }
};

#endif