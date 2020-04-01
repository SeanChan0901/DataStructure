#pragma once
#include <iostream>

template<typename T>
struct chainNode {
  // 数据成员
  T element;
  chainNode<T>* next;  // 链域

  // 方法
  chainNode() {}
  chainNode(const T& element) { 
    this->element = element; 
    next = NULL;
  };
  chainNode(const T& element, chainNode<T>* next) {
    this->element = element;
    this->next = next;
  }
};