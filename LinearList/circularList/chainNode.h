#pragma once

template <typename T>
struct chainNode {
  // ���ݳ�Ա
  T element;
  chainNode<T>* next;

  //������Ա
  chainNode() {};
  chainNode(const T& element) {
    this->element = element;
    next = NULL;
  };
  chainNode(const T& element, chainNode<T>* next) {
    this->element = element;
    this->next = next;
  };
};