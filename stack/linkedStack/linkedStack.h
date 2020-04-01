#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "myExceptions.h"
#include "stack.h"
#include "ChainNode.h"

template <typename T>
class linkedStack : public stack<T> {
 public:
  linkedStack(int initial_capacity = 10) {
    stackTop == NULL;
    stackSize == 0;
  };
  ~linkedStack();

  // ADT
  bool empty() const { return stackSize == 0; };
  int size() const { return stackSize; };
  T& top() const {
    if (stackSize == 0) throw stackEmpty();
    return stackTop->element;
  };
  void pop();
  void push(const T& the_element) {
    stackTop = new chainNode<T>(the_element, stackTop);
    stackSize++;
  }

 protected:
  chainNode<T>* stackTop;  // 栈顶指针
  int stackSize;  // 栈元素个数
};

template<typename T>
void linkedStack<T>::pop() {
  if (stackSize == 0) {
    throw stackEmpty();
  }

  chainNode<T>* nextNode = stackTop->next;
  delete
      [] stackTop;  // 删除放中间，避免没有删除成功又令指针指向新的地方造成内存泄漏
  stackTop = nextNode;
  stackSize--;
};

template<typename T>
linkedStack<T>::~linkedStack() {
  while (stackTop != NULL) {
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
  }
};