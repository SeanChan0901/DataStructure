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
  chainNode<T>* stackTop;  // ջ��ָ��
  int stackSize;  // ջԪ�ظ���
};

template<typename T>
void linkedStack<T>::pop() {
  if (stackSize == 0) {
    throw stackEmpty();
  }

  chainNode<T>* nextNode = stackTop->next;
  delete
      [] stackTop;  // ɾ�����м䣬����û��ɾ���ɹ�����ָ��ָ���µĵط�����ڴ�й©
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