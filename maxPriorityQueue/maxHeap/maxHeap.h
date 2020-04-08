#include <algorithm>
#include <iostream>
#include <sstream>

#include "functionfOfArray.h"
#include "maxPriorityQueue.h"
#include "myExceptions.h"

template <typename T>
class maxHeap : public maxPriorityQueue<T> {
 public:
  maxHeap(int initialCapacity = 10);
  ~maxHeap() { delete[] heap; };
  bool empty() const { return heapSize == 0; };
  int size() const { return heapSize; };
  const T& top() const {  // 返回队首元素
    if (heapSize == 0) throw queueEmpty();
    return heap[1];
  }
  void pop();                // 出队列
  void push(const T&);       // 入队列
  void initialzie(T*, int);  // 舒适化大根堆（堆有序化）
  void deactivateArray() {   // 清空堆
    heap = NULL;
    arrayLength = heapSize = 0;
  };
  void output(std::ostream& out) const;

 protected:
  int heapSize;     // 堆的大小
  int arrayLength;  // 数组容量
  T* heap;          // 大根堆
};

template <typename T>
maxHeap<T>::maxHeap(int initialCapacity) {
  // 构造函数
  if (initialCapacity < 1) {
    std::ostringstream s;
    s << "Initial capacity = " << initialCapacity << "Must be > 0";
    throw IllegalParameterValue(s.str());
  }

  arrayLength = initialCapacity + 1;  // heap[0]不使用
  heap = new T[arrayLength];
  heapSize = 0;
};

template <typename T>
void maxHeap<T>::push(const T& theElement) {
  // 把元素theElement压入堆
  // 必要时增加数组长度
  if (heapSize == arrayLength - 1) {
    // 数组长度加倍
    ChangeLength1D(heap, arrayLength, 2 * arrayLength);
    arrayLength *= 2;
  }

  // 为元素theElement寻找合适的位置
  // 上浮
  int currentNode = ++heapSize;  // size增加，currentNode初始化为最后一个节点
  while (currentNode != 1 && heap[currentNode / 2] < theElement) {
    // 上浮过程
    heap[currentNode] = heap[currentNode / 2];
    currentNode /= 2;
  }
  heap[currentNode] = theElement;  // 插入对应的位置
};

template <typename T>
void maxHeap<T>::pop() {
  // 删除大根堆的最大元素
  // 堆空，抛出异常
  if (heapSize == 0) throw queueEmpty();

  // 删除最大元素
  heap[1].~T();

  // 删除最后一个元素
  T lastElement = heap[heapSize--];

  // 从根开始为最后一个元素寻找新的位置
  int currentNode = 1;
  int child = 2;
  while (child <= heapSize) {  // 还没到堆末
    // heap[child]应该是currentNode最大的孩子
    if (child < heapSize &&
        heap[child] < heap[child + 1])  // 如果有两个孩子取最大的孩子
      child++;

    //  可以把lastElement放在heap[currnetNode]吗
    if (lastElement >= heap[child]) break;  // 可以

    //不可以，将currentNode下沉
    heap[currentNode] = heap[child];
    currentNode = child;
    child *= 2;  // 左孩子
  }
  // child没有左孩子了（叶子节点）
  // 又或者找到堆中的位置了
  heap[currentNode] = lastElement;  // 插入该位置
};

template <typename T>
void maxHeap<T>::initialzie(T* theHeap, int theSize) {
  // 在数组theHeap[1:theSize]中建大根堆
  delete[] heap;  // 删除堆
  heap = theHeap;
  heapSize = theSize;

  // 堆化
  for (int root = heapSize / 2; root >= 1; root--) {
    // 从拥有叶子节点的最后一个节点开始（root=heapSize/2），从右到左，从下到上依次将root=heapsize/2堆化
    T rootElement = heap[root];

    // 为元素rootElement寻找位置
    int child = 2 * root;  // rootElement的孩子
    while (child <= heapSize) {
      // heap[child]是兄弟中的较大者
      if (child < heapSize && heap[child] < heap[child + 1]) child++;

      // 可以把元素rootElement放在heap[child/2]位置上吗
      if (rootElement >= heap[child]) break;  // 可以

      // 不可以
      heap[child / 2] = heap[child];  // 下沉
      child *= 2;
    }
    heap[child / 2] = rootElement;
  }
};

template <class T>
void maxHeap<T>::output(std::ostream& out) const {  // 输出堆
  copy(heap + 1, heap + heapSize + 1,
       std::ostream_iterator<T>(std::cout, "  "));
};

// 重载 <<
template <class T>
std::ostream& operator<<(std::ostream& out, const maxHeap<T>& x) {
  x.output(out);
  return out;
};