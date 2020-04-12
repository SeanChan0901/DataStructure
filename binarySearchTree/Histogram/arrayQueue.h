#pragma once
#include <iostream>
#include <sstream>
#include "myExceptions.h"
#include "functionfOfArray.h"
#include "queue.h"

// 环形队列
template <typename T>
class arrayQueue : public queue<T> {
 public:
  arrayQueue(int initialCapacity = 10);
  ~arrayQueue() { delete[] queue; }
  bool empty() const { return theFront == theBack; }  // 队首指针等于队尾means队空
  int size() const { return (theBack - theFront + arrayLength) % arrayLength; }  // 元素个数
  T& front() const{  // return front element
    if (theFront == theBack) throw queueEmpty();
    return queue[(theFront + 1) % arrayLength];
  }
  T& back() const{  // return theBack element
    if (theFront == theBack) throw queueEmpty();
    return queue[theBack];
  }
  void pop() {  // remove theFront element
    if (theFront == theBack) throw queueEmpty();
    theFront = (theFront + 1) % arrayLength;  // 首元素前移一个位置，把前面那个覆盖掉
    queue[theFront].~T();  // destructor for T
  }
  void push(const T& theElement);

 private:
   // 注意为了方便使用front和back都是索引值
  int theFront;     // 1 counterclockwise from theFront element 
  int theBack;      // position of theBack element
  int arrayLength;  // queue capacity
  T* queue;         // element array
};

template<typename T>
arrayQueue<T>::arrayQueue(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "Initial capacity = " << initial_capacity << " Must be > 0";
    throw IllegalParameterValue(s.str());
  }
  arrayLength = initial_capacity;
  queue = new T[arrayLength];
  theFront = 0;
  theBack = 0;
}

template<typename T>
void arrayQueue<T>::push(const T& the_element) {
  if ((theBack + 1) % arrayLength ==
      theFront) {  // 如果队列满（size=arrayLength-1）
    T* newQueue = new T[2 * arrayLength];  // 开辟新的空间（2倍）

    // 复制原队列
    int start = (theFront + 1) % arrayLength;  // 队首元素在数组中的索引值
    if (start < 2)  // 数组被拉直的时候没有被拆成两段
      std::copy(queue + start, queue + start + arrayLength - 1,  // arrayLength-1才是元素的个数
                newQueue);  // 直接复制过去
    else {                  // 拉成两段的话
      std::copy(queue + start, queue + arrayLength,
                newQueue);  // 后面那段先复制
      std::copy(queue, queue + theBack + 1,
                newQueue + arrayLength - start);  // 复制前面那一段
    }
    // 这个theFront就等于start前面一个位置（逻辑上）于是就是新数组的最后一个位置
    theFront = 2 * arrayLength - 1;
    theBack = arrayLength - 2;  // 记住环形队列最大元素个数是arrayLength-1
    arrayLength *= 2;           // 倍增
    delete[] queue;             // 删除原来的
    queue = newQueue;
  }
  theBack = (theBack + 1) % arrayLength;
  queue[theBack] = the_element;
};
