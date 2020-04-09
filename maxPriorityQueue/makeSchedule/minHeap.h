
#pragma once

#include <algorithm>
#include <sstream>

#include "functionfOfArray.h"
#include "minPriorityQueue.h"
#include "myExceptions.h"

using namespace std;

template <class T>
class minHeap : public minPriorityQueue<T> {
 public:
  minHeap(int initialCapacity = 10);
  ~minHeap() { delete[] heap; }
  bool empty() const { return heapSize == 0; }
  int size() const { return heapSize; }
  const T& top() const{  
    if (heapSize == 0) throw queueEmpty();
    return heap[1];
  }
  void pop();
  void push(const T&);
  void initialize(T*, int);
  void deactivateArray() {
    heap = NULL;
    arrayLength = heapSize = 0;
  }
  void output(ostream& out) const;

 private:
  int heapSize;     // 堆中成员个数
  int arrayLength;  // 数组容量
  T* heap;          // 优先级元素
};

template <class T>
minHeap<T>::minHeap(int initialCapacity) {  // Constructor.
  if (initialCapacity < 1) {
    ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw IllegalParameterValue(s.str());
  }
  arrayLength = initialCapacity + 1;
  heap = new T[arrayLength];
  heapSize = 0;
};

template <class T>
void minHeap<T>::push(const T& theElement) {  // 加入一个元素

  // 查看数组长度是否够用
  if (heapSize == arrayLength - 1) {  // double array length
    ChangeLength1D(heap, arrayLength, 2 * arrayLength);
    arrayLength *= 2;
  }

  // 为theElement寻找新位置
  // currentNode从底上浮
  int currentNode = ++heapSize;
  while (currentNode != 1 && heap[currentNode / 2] > theElement) {
    heap[currentNode] = heap[currentNode / 2];
    currentNode /= 2;
  }

  heap[currentNode] = theElement;
};

template <class T>
void minHeap<T>::pop() {  // 删除最小元素

  if (heapSize == 0)  // heap empty
    throw queueEmpty();

  // 删除最小元素
  heap[1].~T();

  // 把最后的叶子移到此处
  T lastElement = heap[heapSize--];

  // 为lastElement寻找位置
  int currentNode = 1,
      child = 2;  // currentNode的子女
  while (child <= heapSize) {
    // 比较左右孩子，选小的那个
    if (child < heapSize && heap[child] > heap[child + 1]) child++;

    // 是否能插入此位置
    if (lastElement <= heap[child]) break;  // 是

    // 否
    heap[currentNode] = heap[child];  // 下沉
    currentNode = child;
    child *= 2;
  }
  heap[currentNode] = lastElement;
};

template <class T>
void minHeap<T>::initialize(T* theHeap,
                            int theSize) {  // 初始化[1:theSize].
  delete[] heap;
  heap = theHeap;
  heapSize = theSize;
  // 从最后一个叶子节点的双亲开始，一次查看是否为小根堆，若不是则改为小根堆
  for (int root = heapSize / 2; root >= 1; root--) {
    T rootElement = heap[root];

    int child = 2 * root;
    while (child <= heapSize) {
      if (child < heapSize && heap[child] > heap[child + 1]) child++;

      if (rootElement <= heap[child]) break;

      heap[child / 2] = heap[child];
      child *= 2;
    }
    heap[child / 2] = rootElement;
  }
};

template <class T>
void minHeap<T>::output(ostream& out) const {
  copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
};

// overload <<
template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& x) {
  x.output(out);
  return out;
};
