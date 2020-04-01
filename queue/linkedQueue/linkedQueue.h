#pragma once
#include <sstream>
#include "myExceptions.h"
#include "queue.h"
#include "ChainNode.h"

template <typename T>
class linkedQueue :public queue<T>{
 public:
   // ���캯�� ��������
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
  chainNode<T>* queueFront;  // ָ���һ��Ԫ�أ�����Ԫ��
  chainNode<T>* queueBack;  // ָ���βԪ��
  int queueSize;
};

template<typename T>
linkedQueue<T>::~linkedQueue() {  // ��Ͷ��ʼɾ
  while (queueFront != NULL) {
    chainNode<T>* nextNode = queueFront->next;
    delete queueFront;
    queueFront = queueFront->next;
  }
  queueBack = NULL;
};

template<typename T>
void linkedQueue<T>::pop() {
  if (queueFront == NULL) {  // �ն���
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

  // �ն����
  if (queueSize == 0) {
    queueFront = newNode;
  } else {
    queueBack->next = newNode;
  }
  queueBack = newNode; 
  queueSize++;
};