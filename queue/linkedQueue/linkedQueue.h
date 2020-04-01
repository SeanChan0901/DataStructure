#pragma once
#include <sstream>
#include "myExceptions.h"
#include "queue.h"
#include "ChainNode.h"

template <typename T>
class linkedQueue :public queue<T>{
 public:
   // 构造函数 析构函数
  linkedQueue(int initial_capacity = 10) {
    queueFront = NULL;
    queueSize = 0;
    queueBack = NULL;
  }
  ~linkedQueue();

  // ADT
  bool empty() const { return queueSize == 0; };
  int size() const { return queueSize; }
  T& front() const {
    if (queueSize == 0) {
      throw queueEmpty();
    }
    return queueFront->element;
  }
  T& back() const {
    if (queueSize == 0) {
      throw queueEmpty();
    }
    return queueBack->element;
  }
  void pop();
  void push(const T&);

 protected:
  chainNode<T>* queueFront;  // 指向第一个元素：队首元素
  chainNode<T>* queueBack;  // 指向队尾元素
  int queueSize;
};

template<typename T>
linkedQueue<T>::~linkedQueue() {  // 从投开始删
  while (queueFront != NULL) {
    chainNode<T>* nextNode = queueFront->next;
    delete queueFront;
    queueFront = queueFront->next;
  }
  queueBack = NULL;
};

template<typename T>
void linkedQueue<T>::pop() {
  if (queueFront == NULL) {  // 空队列
    throw queueEmpty();
  }

  chainNode<T>* nextNode = queueFront->next;
  delete queueFront;
  queueFront = nextNode;
  queueSize--;
};

template<typename T>
void linkedQueue<T>::push(const T& the_element) {
  chainNode<T>* newNode = new chainNode<T>(the_element, NULL);

  // 空队入队
  if (queueSize == 0) {
    queueFront = newNode;
  } else {
    queueBack->next = newNode;
  }
  queueBack = newNode; 
  queueSize++;
};