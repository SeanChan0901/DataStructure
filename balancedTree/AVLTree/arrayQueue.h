#pragma once
#include <iostream>
#include <sstream>
#include "myExceptions.h"
#include "functionfOfArray.h"
#include "queue.h"

// ���ζ���
template <typename T>
class arrayQueue : public queue<T> {
 public:
  arrayQueue(int initialCapacity = 10);
  ~arrayQueue() { delete[] queue; }
  bool empty() const { return theFront == theBack; }  // ����ָ����ڶ�βmeans�ӿ�
  int size() const { return (theBack - theFront + arrayLength) % arrayLength; }  // Ԫ�ظ���
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
    theFront = (theFront + 1) % arrayLength;  // ��Ԫ��ǰ��һ��λ�ã���ǰ���Ǹ����ǵ�
    queue[theFront].~T();  // destructor for T
  }
  void push(const T& theElement);

 private:
   // ע��Ϊ�˷���ʹ��front��back��������ֵ
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
      theFront) {  // �����������size=arrayLength-1��
    T* newQueue = new T[2 * arrayLength];  // �����µĿռ䣨2����

    // ����ԭ����
    int start = (theFront + 1) % arrayLength;  // ����Ԫ���������е�����ֵ
    if (start < 2)  // ���鱻��ֱ��ʱ��û�б��������
      std::copy(queue + start, queue + start + arrayLength - 1,  // arrayLength-1����Ԫ�صĸ���
                newQueue);  // ֱ�Ӹ��ƹ�ȥ
    else {                  // �������εĻ�
      std::copy(queue + start, queue + arrayLength,
                newQueue);  // �����Ƕ��ȸ���
      std::copy(queue, queue + theBack + 1,
                newQueue + arrayLength - start);  // ����ǰ����һ��
    }
    // ���theFront�͵���startǰ��һ��λ�ã��߼��ϣ����Ǿ�������������һ��λ��
    theFront = 2 * arrayLength - 1;
    theBack = arrayLength - 2;  // ��ס���ζ������Ԫ�ظ�����arrayLength-1
    arrayLength *= 2;           // ����
    delete[] queue;             // ɾ��ԭ����
    queue = newQueue;
  }
  theBack = (theBack + 1) % arrayLength;
  queue[theBack] = the_element;
};
