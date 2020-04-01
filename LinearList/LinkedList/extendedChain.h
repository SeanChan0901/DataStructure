#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include "ChainNode.h"
#include "chain.h"
#include "extendedLinearList.h"
#include "myExceptions.h"

template <typename T>
class extendedChain : public extendedLinearList<T>, public chain<T> {
 public:
  // ���캯�������ƹ��죬��������
  extendedChain(int initial_capacity = 10) : chain<T>(initial_capacity){};  // ֱ����chain��
  extendedChain(const extendedChain<T>& c) : chain<T>(c){};  // ֱ����chain��

  // ADT
  bool empty() const { return chain<T>::empty(); };
  int size() const { return chain<T>::size(); };
  T& get(int the_index) const { return chain<T>::get(the_index); };
  int indexOf(const T& the_element) const {
    return chain<T>::indexOf(the_element);
  };
  void erase(int the_index);
  void insert(int the_index, const T& the_element);
  void output(std::ostream& out) const { chain<T>::output(out); };
  void clear();
  void push_back(const T& the_element);

  // ������Ա�У�firstNode��listSize��checkIndex�����ˣ���չ���¾Ϳ�����
 protected:
  chainNode<T>* lastNode;
};


// erase
template <typename T>
void extendedChain<T>::erase(int the_index) {
  chain<T>::checkIndex(the_index);     // �жϺϷ���
  chainNode<T>* deleteNode;  // Ҫɾ���Ľڵ��ָ��
  if (the_index == 0) {      // ���ɾ�����Ǳ��׽ڵ�
    deleteNode = chain<T>::firstNode;
    chain<T>::firstNode = chain<T>::firstNode->next;  // ����firstNode
  } else {
    chainNode<T>* p = chain<T>::firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // �ҵ�Ҫɾ���ڵ��ǰ���ڵ�
      p = p->next;
    }
    deleteNode = p->next;        // �ҵ�Ҫɾ���Ľڵ�
    p->next = deleteNode->next;  // ����
    if (deleteNode == lastNode) lastNode = p;  // �������һ���ڵ�
  }
  chain<T>::list_size--;
  delete deleteNode;
};

// insert
template <typename T>
void extendedChain<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > chain<T>::list_size) {  // �ж������Ϸ���
    std::ostringstream s;
    s << "index = " << the_index << " size = " << chain<T>::list_size;
    throw IllegalIndex(s.str());
  }

  if (the_index == 0) {
    chain<T>::firstNode = new chainNode<T>(the_element, chain<T>::firstNode);  // ��0��λ�ò�
  } else {
    chainNode<T>* p = chain<T>::firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // �ҵ�Ҫ����λ�õ�ǰһ��λ��
      p = p->next;
    }
    p->next = new chainNode<T>(the_element, p->next);
    if (chain<T>::list_size == the_index)  // ���Ҫ�嵽����λ��
      lastNode = p->next;
  }
  chain<T>::list_size++;
};

// clear
template <typename T>
void extendedChain<T>::clear() {
  while (chain<T>::firstNode != NULL) {
    chainNode<T>* nexteNode = chain<T>::firstNode->next;
    delete chain<T>::firstNode;
    chain<T>::firstNode=nexteNode;
  }
  chain<T>::list_size = 0;
};

// push_back
template <typename T>
void extendedChain<T>::push_back(const T& the_element) {
  chainNode<T>* newNode = new chainNode<T>(the_element, NULL);  // �½��ڵ�
  if (chain<T>::firstNode == NULL)
    chain<T>::firstNode = lastNode = newNode;
  else {
    lastNode->next = newNode;
    lastNode = newNode;
  }
  chain<T>::list_size++;
};