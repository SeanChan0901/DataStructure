#pragma once

template <typename T>
struct chainNode {
  // 数据成员
  T element;
  chainNode<T>* next;

  //函数成员
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