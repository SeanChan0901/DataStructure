#pragma once
// 优先级队列的抽象类
template <typename T>
class minPriorityQueue {
 public:
  virtual ~minPriorityQueue(){};
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual const T& top() const = 0;
  virtual void pop() = 0;
  virtual void push(const T& theElement) = 0;
};