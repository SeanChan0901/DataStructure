#ifndef functionOfArray_
#define functionOfArray_

#include <math.h>

#include <algorithm>
#include <iostream>

#include "myExceptions.h"

template <typename T>
void ChangeLength1D(T*& a, int old_length, int new_length) {
  if (new_length < 0) throw IllegalParameterValue("length must be > 0");
  T* temp = new T[new_length];                    // ������
  int number = std::min(old_length, new_length);  // ȷ����Ҫ���Ƶ�Ԫ�ظ���
  std::copy(a, a + number, temp);  // ��鿴��������end()ָ��ĵ������Ǹ�λ��
  delete[] a;
  a = temp;
};  // ����һά����ĳ���

// ������������������һ����ά����
template <typename T>
bool make2dArray(T**& x, int numberOfRows,
                 int numberOfColumns) {  // ������ά����

  try {
    // ����һάshuzu
    x = new T*[numberOfRows];

    // Ϊÿ�з�������
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