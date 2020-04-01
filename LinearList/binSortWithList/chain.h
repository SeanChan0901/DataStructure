#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include "ChainNode.h"
#include "LinearList.h"
#include "myExceptions.h"
#include "studentRecord.h"

template <typename T>
class chain : public LinearList<T> {
 public:
  // ���캯�������ƹ��죬��������
  chain(int initial_capacity = 10);
  chain(const chain<T>&);
  ~chain();

  // iterator
  class iterator {
   public:
    // ioterator_traits
    typedef std::forward_iterator_tag
        iterator_category;  // ��ǰ��������ֻ��++ û��--
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::ptrdiff_t difference_type;

    // ���캯����ȱʡֵ��ΪNULL
    iterator(chainNode<T>* the_node = NULL) { node = the_node; };

    // ������
    T& operator*() const { return node->element; };
    T* operator->() const { return &(node->element); };

    // �������ӷ�
    iterator& operator++() {
      node = node->next;  // λ�ü�һ
      return *this;
    };

    // ����++ ���ʽʹ�������Լ�
    iterator operator++(int) {
      iterator old = *this;
      node = node->next;
      return old;
    };

    // ���� (���ص�˫Ŀ����������ĳ��ĳ�Ա��ֻ��Ҫһ������)
    bool operator==(const iterator right) const { return node == right.node; };
    bool operator!=(const iterator right) const { return node != right.node; };

    //����
   protected:
    chainNode<T>* node;  // ��������λ��
  };

  // ����������
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

  // ���������
  T& operator[](int the_index);
  bool operator==(const chain<T>& a_chain);
  bool operator!=(const chain<T>& a_chain);

  // ��������
  void reverse();             // ��ת����
  void leftShift(int count);  // ����countλ
  // ������� �ϲ���ab�ǿձ�This�õ���ab�Ľڵ�ռ�,�ϲ���a,bΪ��
  void meld(chain<T>& a, chain<T>& b);
  // �����������a��b merge�ϲ���a,bΪ��
  void merge(chain<T>& a, chain<T>& b);
  // ���α���Ϊ������a�а�������Ϊ������Ԫ��,b����ʣ��Ԫ�أ������õĴ˱�Ŀռ䲻�������µĿռ�
  void split(chain<T>& a, chain<T>& b);
  // ѭ������
  void circularShift(int count);
  // ��������,��������Χ
  void binSort(int range);

 protected:
  void checkIndex(int the_index) const;
  chainNode<T>* firstNode;
  int list_size;
};

// �ж������Ϸ���
template <typename T>
void chain<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// ���캯��
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

// ���ƹ��캯��
template <typename T>
chain<T>::chain(const chain<T>& the_list) {
  list_size = the_list.list_size;
  if (list_size == 0) {
    firstNode = NULL;
    return;
  }
  //����Ϊ�ǿ�
  chainNode<T>* sourceNode = the_list.firstNode;  // ָ��Դ��������ڿ�����ָ��
  firstNode = new chainNode<T>(sourceNode->element);  // �µ�firstNode
  sourceNode = sourceNode->next;
  chainNode<T>* targetNode = firstNode;  // ָ����������ڿ�����ָ��

  while (sourceNode != NULL) {
    targetNode->next = new chainNode<T>(sourceNode->element);  // ������һ���ڵ�
    targetNode = targetNode->next;
    sourceNode = sourceNode->next;
  }
  targetNode->next = NULL;
};

// ��������
template <typename T>
chain<T>::~chain() {
  while (firstNode != NULL) {                    // ���ǿձ�
    chainNode<T>* targetNode = firstNode->next;  // ָ����һ��Ԫ��
    delete firstNode;                            // ɾ����Ԫ��
    firstNode = targetNode;
  }
};

// get
template <typename T>
T& chain<T>::get(int the_index) const {
  checkIndex(the_index);  // �ж������Ϸ���
  chainNode<T>* currentNode = firstNode;
  for (int i = 0; i < the_index; i++) {
    if (i != the_index) currentNode = currentNode->next;
  }
  return currentNode->element;
};

// indexOf  �Ҳ�������-1
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
  checkIndex(the_index);     // �жϺϷ���
  chainNode<T>* deleteNode;  // Ҫɾ���Ľڵ��ָ��
  if (the_index == 0) {      // ���ɾ�����Ǳ��׽ڵ�
    deleteNode = firstNode;
    firstNode = firstNode->next;  // ����firstNode
  } else {
    chainNode<T>* p = firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // �ҵ�Ҫɾ���ڵ��ǰ���ڵ�
      p = p->next;
    }
    deleteNode = p->next;        // �ҵ�Ҫɾ���Ľڵ�
    p->next = deleteNode->next;  // ����
  }
  list_size--;
  delete deleteNode;
};

// insert
template <typename T>
void chain<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 || the_index > list_size) {  // �ж������Ϸ���
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }

  if (the_index == 0) {
    firstNode = new chainNode<T>(the_element, firstNode);  // ��0��λ�ò�
  } else {
    chainNode<T>* p = firstNode;
    for (int i = 0; i < the_index - 1; i++) {  // �ҵ�Ҫ����λ�õ�ǰһ��λ��
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
  if (list_size != a_chain.list_size) {  // ���Ȳ���ȣ�����ͬ
    return false;
  }
  chainNode<T>* a_currentNode = firstNode;
  chainNode<T>* b_currentNode = a_chain.firstNode;
  for (int i = 0; i < list_size; i++) {
    if (a_currentNode != NULL &&
        a_currentNode->element ==
            b_currentNode->element) {  // ��û��β���Ҳ���ͬ
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
  for (int i = 0; i < list_size / 2; i++) {  // ��������Ϊlist_size/2
    // ���ڽ����������ڵ�
    chainNode<T>* a_node = firstNode;
    chainNode<T>* b_node = firstNode;
    T temp;                        // ������ʱ����
    for (int j = 0; j < i; j++) {  // ���±�Ϊi��Ԫ��
      a_node = a_node->next;
    }
    for (int j = 0; j < list_size - i - 1;
         j++) {  // ���±�Ϊ list_size-i-1��Ԫ��
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
  for (int i = 0; i < count; i++) {  // ��ǰ���ɾ��
    if (list_size > 0) {
      chainNode<T>* currentNode = firstNode;
      firstNode = firstNode->next;
      delete currentNode;
      list_size--;
    } else
      break;  // �����ˣ�ֱ������
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
  this->clear();  // ��ձ���
  // a��b�ȳ�����b��a������ôa��b��û��
  // a��b����a��û��
  // �ж�a��b�Ƿ�������һ�����ǿձ�
  if (a.firstNode == NULL || b.firstNode == NULL) {
    // �������ôֱ����firstNode=�ǿձ��ͷ�ڵ�
    firstNode = (a.firstNode == NULL ? b.firstNode : a.firstNode);
    list_size = a.list_size + b.list_size;  // ��С����
    a.firstNode = b.firstNode = NULL;       // ���ÿ�
    a.list_size = b.list_size = 0;          // ���ÿ�
    return;                                 // ����
  }

  firstNode = a.firstNode;                              // a��b�����ǿձ�
  while (a.firstNode != NULL && b.firstNode != NULL) {  // ���������
    chainNode<T>* a_node = a.firstNode->next;  // a���α꣺��һ��λ��
    chainNode<T>* b_node = b.firstNode->next;  // b���α꣺��һ��λ��
    a.firstNode->next = b.firstNode;           // ����
    if (a_node != NULL) b.firstNode->next = a_node;  // ����
    a.firstNode = a_node;                            // ����a��λ��
    b.firstNode = b_node;                            // ����b��λ��
  }
  list_size = a.list_size + b.list_size;  // ��С����
  a.firstNode = b.firstNode = NULL;       // ���ÿ�
  a.list_size = b.list_size = 0;          // ���ÿ�
  return;
};

template <typename T>
void chain<T>::merge(chain<T>& a, chain<T>& b) {
  this->clear();
  // a��b�ȳ�����b��a������ôa��b��û��
  // a��b����a��û��
  // �ж�a��b�Ƿ�������һ�����ǿձ�
  if (a.firstNode == NULL || b.firstNode == NULL) {
    // �������ôֱ����firstNode=�ǿձ��ͷ�ڵ�
    firstNode = (a.firstNode == NULL ? b.firstNode : a.firstNode);
    list_size = a.list_size + b.list_size;  // ��С����
    a.firstNode = b.firstNode = NULL;       // ���ÿ�
    a.list_size = b.list_size = 0;          // ���ÿ�
    return;                                 // ����
  }
  // ȷ��ͷ�ڵ�
  if (a.firstNode->element <= b.firstNode->element) {
    firstNode = a.firstNode;  // aС��a��ͷ�ڵ�
    a.firstNode = a.firstNode->next;
  } else {
    firstNode = b.firstNode;  // bС��b��ͷ�ڵ�
    b.firstNode = b.firstNode->next;
  }

  chainNode<T>* currentNode = firstNode;
  while (a.firstNode != NULL && b.firstNode != NULL) {
    if (a.firstNode->element <=
        b.firstNode->element) {  // a��bС����ô��a������
      currentNode->next = a.firstNode;
      a.firstNode = a.firstNode->next;
      currentNode = currentNode->next;
    } else {  // b��aС����ô��b������
      currentNode->next = b.firstNode;
      b.firstNode = b.firstNode->next;
      currentNode = currentNode->next;
    }
  }
  // ��û��
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
  // ���a��b
  a.clear();
  b.clear();

  chainNode<T>* currentNode_a = a.firstNode = firstNode->next;
  chainNode<T>* currentNode_b = b.firstNode = firstNode;
  while (currentNode_a != NULL && currentNode_b != NULL) {
    currentNode_b->next = currentNode_a->next;  // ���ӣ���ͼ���������
    currentNode_b = currentNode_b->next;
    currentNode_a->next = currentNode_b->next;
    currentNode_a = currentNode_a->next;
  }
  // ����֮��Ҫôͬʱ�գ�Ҫôa��b����
  currentNode_b->next = NULL;             // �Է���һ����b���
  a.list_size = list_size / 2;            // ���³���
  b.list_size = list_size - a.list_size;  // ���³���
  list_size = 0;
  firstNode = NULL;  // �ձ�
};

template <typename T>
void chain<T>::circularShift(int count) {
  chainNode<T>* newFirstNode = firstNode;
  for (int i = 0; i < count;
       i++) {  // ѭ������count��λ�ú��ҵ���Ҫ����Ϊͷ�ڵ�Ľڵ�
    if (newFirstNode->next == NULL) {
      newFirstNode = firstNode;
    } else {
      newFirstNode = newFirstNode->next;
    }
  }
  chainNode<T>* oldBackNode = newFirstNode;
  while (oldBackNode->next != NULL) {  // �ҵ�ԭ����β�ڵ�
    oldBackNode = oldBackNode->next;
  }
  oldBackNode->next =
      firstNode;  // ��β������һ���ڵ�Ϊ�ɵ�ͷ�ڵ㣨�������γ�һ�����������������µ�β��������Ͽ�����
  chainNode<T>* newBackNode = firstNode;  // �µ�β�ڵ�
  while (newBackNode->next != newFirstNode) {
    newBackNode = newBackNode->next;
  }
  newBackNode->next = NULL;  // ��β��

  firstNode = newFirstNode;  // ����firstNode;
};
// �������򣬳�Ա����
template <typename T>
void chain<T>::binSort(int range) {
  // ��������ʼ������
  chainNode<T>**bottom,
      **top;  // ����һ��ָ��ָ��chainNode<T>���͵�ָ�룩��ָ��
  // һ��range+1������,bottom[the_bin]ָ��������Ӻ�Ϊthe_bin�����Ԫ��
  bottom = new chainNode<T>*[range + 1];
  // һ��range + 1������, top[the_bin] ָ��������Ӻ�Ϊthe_bin������Ԫ��
  top = new chainNode<T>*[range + 1];
  for (int b = 0; b <= range; b++) {  // ��ʼ������
    bottom[b] = NULL;                 // ���û���κ�Ԫ��
  }

  // ������ڵ���������
  for (; firstNode != NULL; firstNode = firstNode->next) {
    int the_bin =
        (int)firstNode
            ->element;  // ��Ԫ��ת����int���ͣ��Ѿ����غ���int���������ˣ�
    if (bottom[the_bin] ==
        NULL) {  // ����Ϊ�� ���Ԫ��ֱ�ӷŽ����ӣ�����ʼ��bottom��top
      bottom[the_bin] = top[the_bin] = firstNode;
    } else {                              // ���Ӳ���
      top[the_bin]->next = firstNode;     // �ӵ�������
      top[the_bin] = top[the_bin]->next;  // �������ӵ�top
    }
  }

  // �������еĽڵ��ռ����������
  chainNode<T>* y = NULL;  // ������ڸ��������е�����λ��
  for (int the_bin = 0; the_bin <= range; the_bin++) {  // �����е����ӽ���
    if (bottom[the_bin] != NULL) {                      // ���Ӳ���
      if (y == NULL) {                // ��գ���һ�����ӣ�
        firstNode = bottom[the_bin];  // ��ʼ����
      } else {
        y->next = bottom[the_bin];  // �������Ӵ�������
      }
      y = top[the_bin];  // �ƶ������Ӷ�׼����һ������
    }
  }
  // ������֮��yӦ��ָ��������һ�����յ����ӵ����Ӷ�Ҳ�������������β�ڵ�
  if (y != NULL) {
    y->next = NULL;  // ���������Ԫ�أ���ôβ�ڵ����ΪNULL
  }
  delete[] bottom;
  delete[] top;
};

// ��������
void binSort(chain<studentRecord>& the_chain, int range) {  // range������߷�
  chain<studentRecord>* bin;                                // ��������
  //  [0:5]һ����6�������������СΪrange+1 = 5+1 = 6
  bin = new chain<studentRecord>[range + 1];
  // ����������
  int numberOfElements = the_chain.size();       // ѧ��������
  for (int i = 1; i <= numberOfElements; i++) {  // ��ѧ����������
    studentRecord x = the_chain.get(0);
    the_chain.erase(0);
    bin[x.score].insert(0, x);
  }

  // ���������ռ�Ԫ��
  for (int j = range; j >= 0; j--) {
    while (!bin[j].empty()) {  // �ǿ�
      studentRecord x = bin[j].get(0);
      bin[j].erase(0);
      the_chain.insert(0, x);
    }
  }
  delete[] bin;  // the_chain�����Ѿ��ź������
};