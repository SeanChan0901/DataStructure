#pragma once
#include <iostream>
#include "stack.h"
#include "myExceptions.h"
#include <sstream>
#include "functionfOfArray.h"

template <typename T>
class arrayStack : public stack<T> {
 public:
  arrayStack(int initial_capacity = 10);
  ~arrayStack() { delete[] stack; };

  // ADT
  bool empty() const { return stackTop == -1; }
  int size() const { return stackTop + 1; };  // 栈元素个数等于栈顶+1
  T& top() const {
    if (stackTop == -1) throw stackEmpty();  // 非空时返回栈顶元素
    return stack[stackTop];
  };
  void pop() {
    if (stackTop==-1) {
      throw stackEmpty();
    }
    stack[stackTop--].~T();  // 栈顶索引减一

  }
  void push(const T& the_element);
 protected:
  int stackTop; // 栈顶的索引,=-1时栈为空
  int arrayLength;  // 栈的容量
  T* stack;  // 数组元素
};

// 构造函数
template <typename T>
arrayStack<T>::arrayStack(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "initial capacity = " << initial_capacity << " must be > 1";
    throw IllegalParameterValue(s.str());
  }
  arrayLength = initial_capacity;
  stack = new T[arrayLength];
  stackTop = -1;  // 空栈
};

template<typename T>
void arrayStack<T>::push(const T& the_element) {
  if (stackTop == arrayLength - 1) {
    ChangeLength1D(stack, arrayLength, 2 * arrayLength);
    arrayLength *= 2;
  }
  stack[++stackTop] = the_element;
};