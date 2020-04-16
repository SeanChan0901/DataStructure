#pragma once
#include <iostream>

#include "ChainNode.h"
#include "chain.h"

template <typename T>
class graphChain : public chain<T> {
 public:
  bool eraseElement(int theVertex) {  // 删除theVertex节点
                                    // 返回节点元素的指针
                                    // 如果找不到该元素返回NULL
    chainNode<T>* current = this->firstNode;
    chainNode<T>* trail = NULL;  // 前驱

    // 寻找匹配节点
    while (current != NULL && current->element != theVertex) {
      trail = current;
      current = current->next;
    }

    if (current == NULL)  // no match
      return false;

    // 找到匹配节点
    T* theElement = &(current->element);

    // 从链表中删除节点
    if (trail != NULL)
      trail->next = current->next;
    else
      this->firstNode = current->next;  // currentNode是第一个节点

    delete current;
    this->list_size--;
    return true;
  }
  chainNode<T>* getFirst() const { return this->firstNode; }
};