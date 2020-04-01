#pragma once
#include <iostream>
#include "chainNode.h"
#include "LinearList.h"
#include "myExceptions.h"
#include <sstream>

// ����ͷ�ڵ��˫��ѭ������
template <typename T>
class dLinkedList : public LinearList<T> {
 public:
  dLinkedList(int initial_capacity = 10);
  dLinkedList(const dLinkedList<T>&);
  ~dLinkedList();

  // ADT
  bool empty() const { return list_size == 0; };
  int size() const { return list_size; };
  T& get(int the_index) const;
  int indexOf(const T& the_element) const;
  void erase(int the_index);
  void insert(int the_index, const T& the_element);
  void output(std::ostream& out) const;

 private:
  void checkIndex(int the_index) const;
  chainNode<T>* headerNode;  // ͷ�ڵ�
  int list_size;
};

// �ж������Ϸ���
template <typename T>
void dLinkedList<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// ���캯��
template <typename T>
dLinkedList<T>::dLinkedList(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "initial capacity = " << initial_capacity << "must be > 0";
    throw IllegalParameterValue(s.str());
  }
  headerNode = new chainNode<T>();  // ����ͷ�ڵ㣬����ɶ������
  headerNode->next = headerNode;
  headerNode->previous = NULL;
  list_size = 0;
};

template <typename T>
dLinkedList<T>::dLinkedList(
    const dLinkedList<T>& the_list) {
  list_size = the_list.list_size;
  headerNode = new chainNode<T>();  // ����ͷ�ڵ�
  if (list_size == 0) {
    headerNode->next = headerNode;  // ѭ����
    return;                         // ����ǿձ�ֱ�ӷ���
  }
  //�ǿձ�
  chainNode<T>* sourceNode = the_list.headerNode->next;
  chainNode<T>* targetNode = headerNode;
  while (sourceNode != the_list.headerNode) {
    targetNode->next = new chainNode<T>(targetNode,sourceNode->element);  // ���ƽڵ�
    targetNode = targetNode->next;
    sourceNode = sourceNode->next;
  }
  targetNode->next = headerNode;
};

// get
template <typename T>
T& dLinkedList<T>::get(int the_index) const {
  checkIndex(the_index);  // �ж������Ϸ���
  chainNode<T>* currentNode = headerNode->next;
  for (int i = 0; i < the_index; i++) {
    if (i != the_index) currentNode = currentNode->next;
  }
  return currentNode->element;
};

// indexOf �Ҳ�������-1
template <typename T>
int dLinkedList<T>::indexOf(const T& the_element) const {
  // Ԫ�ط���ͷ�ڵ�
  headerNode->element = the_element;

  // ������������Ԫ��
  chainNode<T>* currentNode = headerNode->next;
  int index = 0;  // ��ǰ����
  while (currentNode->element != the_element) {
    currentNode = currentNode->next;
    index++;
  }
  if (currentNode == headerNode) {  // ����ص�ͷ�ڵ���
    return -1;
  } else {
    return index;
  }
};

template <typename T>
void dLinkedList<T>::erase(int the_index) {
  checkIndex(the_index);  // �鿴�����Ϸ���
  chainNode<T>* deleteNode = headerNode->next;
  if (the_index == 0) {
    headerNode->next = deleteNode->next;
  } else {
    chainNode<T>* p = headerNode->next;
    for (int i = 0; i < the_index - 1; i++) {  // �ҵ�Ҫɾ���Ľڵ��ǰ��
      p = p->next;
    }
    deleteNode = p->next;        // ����Ҫ��ɾ���Ľڵ�
    deleteNode->next->previous = p;
    p->next = deleteNode->next;  // ����
  }
  list_size--;
  delete deleteNode;
};

template <typename T>
void dLinkedList<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > list_size) {  // �ж������Ϸ���
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
  if (the_index == 0) {
    headerNode->next =
        new chainNode<T>(headerNode,the_element, headerNode->next);  //�����0��λ��
    headerNode->next->next->previous = headerNode->next;    // ����
  } else {
    chainNode<T>* p = headerNode->next;
    for (int i = 0; i < the_index - 1; i++) {  // �Ҳ�����ǰ��
      p = p->next;
    }
    p->next = new chainNode<T>(p,the_element, p->next);
    // ����p->nextָ���²���Ľڵ�
    p->next->next->previous = p->next;  // ����
  }
  list_size++;
};

// output
template <typename T>
void dLinkedList<T>::output(std::ostream& out) const {
  for (chainNode<T>* currentNode = headerNode->next; currentNode != headerNode;
       currentNode = currentNode->next) {
    out << currentNode->element << " ";
  }
};

// <<
template <typename T>
std::ostream& operator<<(std::ostream& out,
                         const dLinkedList<T>& x) {
  x.output(out);
  return out;
};

template <typename T>
dLinkedList<T>::~dLinkedList() {
  chainNode<T>* deleteNode = headerNode->next;
  while (deleteNode != headerNode) {
    headerNode->next = deleteNode->next;
    delete deleteNode;
    deleteNode = headerNode->next;
  }
};