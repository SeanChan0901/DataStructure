#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include "ChainNode.h"
#include "LinearList.h"
#include "myExceptions.h"

template <typename T>
class chain : public LinearList<T> {
 public:
  // 构造函数，复制构造，析构函数
  chain(int initial_capacity = 10);
  chain(const chain<T>&);
  ~chain();

  // iterator
  class iterator {
   public:
    // ioterator_traits
    typedef std::forward_iterator_tag
        iterator_category;  // 向前迭代器，只有++ 没有--
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::ptrdiff_t difference_type;

    // 构造函数，缺省值设为NULL
    iterator(chainNode<T>* the_node = NULL) { node = the_node; };

    // 解引用
    T& operator*() const { return node->element; };
    T* operator->() const { return &(node->element); };

    // 迭代器加法
    iterator& operator++() {
      node = node->next;  // 位置加一
      return *this;
    };

    // 后置++ 表达式使用完再自加
    iterator operator++(int) {
      iterator old = *this;
      node = node->next;
      return old;
    };

    // 检验 (重载的双目运算符如果是某类的成员则只需要一个参数)
    bool operator==(const iterator right) const { return node == right.node; };
    bool operator!=(const iterator right) const { return node != right.node; };

    //方法
   protected:
    chainNode<T>* node;  // 迭代器的位置
  };

  // 迭代器函数
  iterator begin() { return iterator(firstNode); };
  iterator end() { return iterator(NULL); };
  // ADT
  bool empty() const { return list_size == 0; };
  int size() const { return list_size; };
  T& get(int the_index) const;
  int indexOf(const T& the_element) const;
  void erase(int the_index);
  void insert(int the_index, const T& the_element);
  void output(std::ostream& out) const;
  void clear();

  // 重载运算符
  T& operator[](int the_index);
  bool operator==(const chain<T>& a_chain);
  bool operator!=(const chain<T>& a_chain);

  // 其他方法
  void reverse();             // 逆转链表
  void leftShift(int count);  // 左移count位
  // 交替包含 合并后ab是空表，This用的是ab的节点空间,合并后a,b为空
  void meld(chain<T>& a, chain<T>& b);
  // 将两个有序表a和b merge合并后a,b为空
  void merge(chain<T>& a, chain<T>& b);
  // 将次表拆分为两个表，a中包含索引为奇数的元素,b包含剩余元素，还是用的此表的空间不允许创建新的空间
  void split(chain<T>& a, chain<T>& b);
  // 循环左移
  void circularShift(int count);

 protected:
  void checkIndex(int the_index) const;
  chainNode<T>* firstNode;
  int list_size;
};

// 判断索引合法性
template <typename T>
void chain<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// 构造函数
template <typename T>
chain<T>::chain(int initial_capacity) {
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "initial capacity = " << initial_capacity << "must be > 0";
    throw IllegalParameterValue(s.str());
  }
  firstNode = NULL;
  list_size = 0;
};

// 复制构造函数
template <typename T>
chain<T>::chain(const chain<T>& the_list) {
  list_size = the_list.list_size;
  if (list_size == 0) {
    firstNode = NULL;
    return;
  }
  //链表为非空
  chainNode<T>* sourceNode = the_list.firstNode;  // 指向源链表的用于拷贝的指针
  firstNode = new chainNode<T>(sourceNode->element);  // 新的firstNode
  sourceNode = sourceNode->next;
  chainNode<T>* targetNode = firstNode;  // 指向本链表的用于拷贝的指针

  while (sourceNode != NULL) {
    targetNode->next = new chainNode<T>(sourceNode->element);  // 复制下一个节点
    targetNode = targetNode->next;
    sourceNode = sourceNode->next;
  }
  targetNode->next = NULL;
};

// 析构函数
template <typename T>
chain<T>::~chain() {
  while (firstNode != NULL) {                    // 不是空表
    chainNode<T>* targetNode = firstNode->next;  // 指向下一个元素
    delete firstNode;                            // 删除本元素
    firstNode = targetNode;
  }
};

// get
template <typename T>
T& chain<T>::get(int the_index) const {
  checkIndex(the_index);  // 判断索引合法性
  chainNode<T>* currentNode = firstNode;
  for (int i = 0; i < the_index; i++) {
    if (i != the_index) currentNode = currentNode->next;
  }
  return currentNode->element;
};

// indexOf  找不到返回-1
template <typename T>
int chain<T>::indexOf(const T& the_element) const {
  chainNode<T>* currentNode = firstNode;
  int index = 0;
  while (currentNode != NULL && currentNode->element != the_element) {
    currentNode = currentNode->next;
    ++index;
  }
  if (currentNode == NULL)
    return -1;
  else
    return index;
};

// erase
template <typename T>
void chain<T>::erase(int the_index) {
  checkIndex(the_index);     // 判断合法性
  chainNode<T>* deleteNode;  // 要删除的节点的指针
  if (the_index == 0) {      // 如果删除的是表首节点
    deleteNode = firstNode;
    firstNode = firstNode->next;  // 更新firstNode
  } else {
    chainNode<T>* p = firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // 找到要删除节点的前驱节点
      p = p->next;
    }
    deleteNode = p->next;        // 找到要删除的节点
    p->next = deleteNode->next;  // 脱链
  }
  list_size--;
  delete deleteNode;
};

// insert
template <typename T>
void chain<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > list_size) {  // 判断索引合法性
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }

  if (the_index == 0) {
    firstNode = new chainNode<T>(the_element, firstNode);  // 第0个位置插
  } else {
    chainNode<T>* p = firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // 找到要插入位置的前一个位置
      p = p->next;
    }
    p->next = new chainNode<T>(the_element, p->next);
  }
  list_size++;
};

// output
template <typename T>
void chain<T>::output(std::ostream& out) const {
  for (chainNode<T>* currentNode = firstNode; currentNode != NULL;
       currentNode = currentNode->next) {
    out << currentNode->element << " ";
  }
};

// <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x) {
  x.output(out);
  return out;
};

// []
template <typename T>
T& chain<T>::operator[](int the_index) {
  checkIndex(the_index);
  chainNode<T>* currentNode = firstNode;
  for (int i = 0; i < the_index; i++) {
    currentNode = currentNode->next;
  }
  return currentNode->element;
};

// ==
template <typename T>
bool chain<T>::operator==(const chain<T>& a_chain) {
  if (list_size != a_chain.list_size) {  // 长度不相等，不相同
    return false;
  }
  chainNode<T>* a_currentNode = firstNode;
  chainNode<T>* b_currentNode = a_chain.firstNode;
  for (int i = 0; i < list_size; i++) {
    if (a_currentNode != NULL &&
        a_currentNode->element ==
            b_currentNode->element) {  // 还没到尾部且不相同
      a_currentNode = a_currentNode->next;
      b_currentNode = b_currentNode->next;
    }
  }
  if (a_currentNode == NULL) {
    return true;
  } else
    return false;
};

template <typename T>
bool chain<T>::operator!=(const chain<T>& a_chain) {
  return (!(*this) == a_chain);
};

template <typename T>
void chain<T>::reverse() {
  for (int i = 0; i < list_size / 2; i++) {  // 交换次数为list_size/2
    // 用于交换的两个节点
    chainNode<T>* a_node = firstNode;
    chainNode<T>* b_node = firstNode;
    T temp;                        // 用于临时保存
    for (int j = 0; j < i; j++) {  // 找下标为i的元素
      a_node = a_node->next;
    }
    for (int j = 0; j < list_size - i - 1;
         j++) {  // 找下标为 list_size-i-1的元素
      b_node = b_node->next;
    }
    temp = a_node->element;
    a_node->element = b_node->element;
    b_node->element = temp;
  }
};

template <typename T>
void chain<T>::leftShift(int count) {
  if (count < 0) {
    throw IllegalParameterValue("ill legal parameter value");
  }
  for (int i = 0; i < count; i++) {  // 把前面的删除
    if (list_size > 0) {
      chainNode<T>* currentNode = firstNode;
      firstNode = firstNode->next;
      delete currentNode;
      list_size--;
    } else
      break;  // 移完了，直接跳出
  }
};

template <typename T>
void chain<T>::clear() {
  while (firstNode != NULL) {
    chainNode<T>* currentNode = firstNode->next;
    delete firstNode;
    firstNode = currentNode;
  }
  list_size = 0;
};

template <typename T>
void chain<T>::meld(chain<T>& a, chain<T>& b) {
  this->clear();  // 清空本表
  // a和b等长或者b比a长，那么a完b还没完
  // a比b长，a还没完
  // 判断a和b是否至少又一个表是空表
  if (a.firstNode == NULL || b.firstNode == NULL) {
    // 如果是那么直接领firstNode=非空表的头节点
    firstNode = (a.firstNode == NULL ? b.firstNode : a.firstNode);
    list_size = a.list_size + b.list_size;  // 大小更新
    a.firstNode = b.firstNode = NULL;       // 表置空
    a.list_size = b.list_size = 0;          // 表置空
    return;                                 // 返回
  }

  firstNode = a.firstNode;                              // a和b都不是空表
  while (a.firstNode != NULL && b.firstNode != NULL) {  // 两表均不空
    chainNode<T>* a_node = a.firstNode->next;  // a的游标：下一个位置
    chainNode<T>* b_node = b.firstNode->next;  // b的游标：下一个位置
    a.firstNode->next = b.firstNode;           // 链接
    if (a_node != NULL) b.firstNode->next = a_node;  // 链接
    a.firstNode = a_node;                            // 更新a本位置
    b.firstNode = b_node;                            // 更新b本位置
  }
  list_size = a.list_size + b.list_size;  // 大小更新
  a.firstNode = b.firstNode = NULL;       // 表置空
  a.list_size = b.list_size = 0;          // 表置空
  return;
};

template <typename T>
void chain<T>::merge(chain<T>& a, chain<T>& b) {
  this->clear();
  // a和b等长或者b比a长，那么a完b还没完
  // a比b长，a还没完
  // 判断a和b是否至少又一个表是空表
  if (a.firstNode == NULL || b.firstNode == NULL) {
    // 如果是那么直接领firstNode=非空表的头节点
    firstNode = (a.firstNode == NULL ? b.firstNode : a.firstNode);
    list_size = a.list_size + b.list_size;  // 大小更新
    a.firstNode = b.firstNode = NULL;       // 表置空
    a.list_size = b.list_size = 0;          // 表置空
    return;                                 // 返回
  }
  // 确定头节点
  if (a.firstNode->element <= b.firstNode->element) {
    firstNode = a.firstNode;  // a小，a做头节点
    a.firstNode = a.firstNode->next;
  } else {
    firstNode = b.firstNode;  // b小，b做头节点
    b.firstNode = b.firstNode->next;
  }

  chainNode<T>* currentNode = firstNode;
  while (a.firstNode != NULL && b.firstNode != NULL) {
    if (a.firstNode->element <=
        b.firstNode->element) {  // a比b小，那么把a链进表
      currentNode->next = a.firstNode;
      a.firstNode = a.firstNode->next;
      currentNode = currentNode->next;
    } else {  // b比a小，那么把b链进表
      currentNode->next = b.firstNode;
      b.firstNode = b.firstNode->next;
      currentNode = currentNode->next;
    }
  }
  // 把没玩
  if (a.firstNode == NULL)
    currentNode->next = b.firstNode;
  else
    currentNode->next = a.firstNode;
  list_size = a.list_size + b.list_size;
  a.list_size = b.list_size = 0;
  a.firstNode = b.firstNode = NULL;
};

template <typename T>
void chain<T>::split(chain<T>& a, chain<T>& b) {
  // 清空a和b
  a.clear();
  b.clear();

  chainNode<T>* currentNode_a = a.firstNode = firstNode->next;
  chainNode<T>* currentNode_b = b.firstNode = firstNode;
  while (currentNode_a != NULL && currentNode_b != NULL) {
    currentNode_b->next = currentNode_a->next;  // 跳接（作图会更清晰）
    currentNode_b = currentNode_b->next;
    currentNode_a->next = currentNode_b->next;
    currentNode_a = currentNode_a->next;
  }
  // 链完之后，要么同时空，要么a空b不空
  currentNode_b->next = NULL;             // 以防万一，把b设空
  a.list_size = list_size / 2;            // 更新长度
  b.list_size = list_size - a.list_size;  // 更新长度
  list_size = 0;
  firstNode = NULL;  // 空表
};

template<typename T>
void chain<T>::circularShift(int count) {
  chainNode<T>* newFirstNode = firstNode;
  for (int i = 0; i < count;
       i++) {  // 循环左移count个位置后找到需要更新为头节点的节点
    if (newFirstNode->next == NULL) {
      newFirstNode = firstNode;
    } else {
      newFirstNode = newFirstNode->next;
    }
  }
  chainNode<T>* oldBackNode = newFirstNode;
  while (oldBackNode->next != NULL) {  // 找到原来的尾节点
    oldBackNode = oldBackNode->next;
  }
  oldBackNode->next = firstNode;  // 老尾部的下一个节点为旧的头节点（连起来形成一个环，方便下面找新的尾部（不会断开））
  chainNode<T>* newBackNode = firstNode;  // 新的尾节点
  while (newBackNode->next != newFirstNode) {
    newBackNode = newBackNode->next;
  }
  newBackNode->next = NULL;  // 新尾部

  firstNode = newFirstNode;  // 更新firstNode;
};