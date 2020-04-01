#pragma once
#include <iostream>
#include <algorithm>
#include <math.h>
#include "myExceptions.h"

template<class T>
void ChangeLength1D(T*& a, int old_length, int new_length) {  
  if (new_length < 0) throw IllegalParameterValue("length must be > 0");
  T* temp = new T[new_length];                           // ������
  int number = std::min(old_length, new_length);  // ȷ����Ҫ���Ƶ�Ԫ�ظ���
  std::copy(a, a + number, temp);  // ��鿴��������end()ָ��ĵ������Ǹ�λ��
  delete []a;
  a = temp;
};  // ����һά����ĳ���

// ������ά����
template <class T>
bool make2dArray(T**& x, int numberOfRows,
                 int numberOfColumns) {  // Create a two dimensional array.

  try {
    // create pointers for the rows
    x = new T*[numberOfRows];

    // get memory for each row
    for (int i = 0; i < numberOfRows; i++) x[i] = new int[numberOfColumns];
    return true;
  } catch (std::bad_alloc) {
    return false;
  }
};