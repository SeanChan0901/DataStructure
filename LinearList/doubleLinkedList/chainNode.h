#pragma once

template <typename T>
struct chainNode {
  // 数据成员
  T element;
  chainNode<T>* next;
  chainNode<T>* previous;
  //函数成员
  chainNode() {};
  chainNode(const T& element) {
    this->element = element;
    next = NULL;
    previous = NULL;
  };
  chainNode(const T& element, chainNode<T>* next_node) {
    this->element = element;
    this->next = next_node;
    this->previous = NULL;
  };
  chainNode(chainNode<T>* previous_node,const T& element) {
    this->element = element;
    this->next = NULL;
    this->previous = previous_node;
  };
  chainNode(chainNode<T>* previous_node, const T& element,
            chainNode<T>* next_node) {
    this->element = element;
    this->next = next_node;
    this->previous = previous_node;
  };
};