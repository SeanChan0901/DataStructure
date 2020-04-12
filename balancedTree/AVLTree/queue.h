#pragma once
#include <iostream>

template <typename T>
class queue {
 public:
  virtual ~queue() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual T& front() const = 0;  // ���ض���Ԫ��
  virtual T& back() const = 0;  // ���ض�βԪ��
  virtual void pop() = 0;       // ɾ������Ԫ��
  virtual void push(const T& the_element) = 0;  // ��Ԫ��element�ӵ���β
};