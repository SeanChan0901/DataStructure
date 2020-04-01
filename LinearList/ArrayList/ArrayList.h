#pragma once
#include <algorithm>
#include <iterator>
#include <sstream>  // ʹ��sstream�����������
#include "LinearList.h"
#include "error.h"
#include "functionfOfArray.h"
#include "myExceptions.h"

template <class T>
class ArrayList : public LinearList<T> {
 public:
  // ���캯�������ƹ��캯������������
  ArrayList(int initial_capacity = 10);  // ���캯�����������鳤��Ĭ�ϳ�ʼ��Ϊ10
  ArrayList(const ArrayList<T>&);  // ���ƹ��캯��

  // ��������

  // ������
  class iterator {
   public:
    // ��C++��typedef���ʵ��˫�������
    typedef std::bidirectional_iterator_tag
        iterator_category;  // ����������Ϊ˫��
    typedef T value_type;   // ���Ա�����ֵ�Ԫ�ص�����
    typedef std::ptrdiff_t difference_type;  // prrdiff_t����ָ��֮�����������
    typedef T* pointer;    // ���Ա�����Ԫ�ص�ָ��
    typedef T& reference;  // ���Ա�����Ԫ�ص�����
    iterator(T* the_psition = 0) { position = the_psition; };  // ��ʼ��������
    ~iterator(){};

    // �����ò�����
    T& operator*() const {
      return *position;
    };  // *�����ò�����������ָ��ָ���Ԫ��
    T* operator->() const {
      return &*position;
    };  // һ��ָ��p->f()ʵ���Ͼ���(*p).f()

    // ��������ֵ����
    iterator& operator++() {  // ǰ��++��������ֵ
      ++position;
      return *this;  // ǰ��++����++֮�����ֵ
    };
    iterator operator++(int) {  // ����++��������ֵ
      iterator old = *this;
      ++position;
      return old;  // ����++����++֮ǰ����ֵ
    };

    // ��������ֵ����
    iterator& operator--() {  // ǰ��--��������ֵ
      --position;
      return *this;
    };
    iterator operator--(int) {  // ����--��������ֵ
      iterator old = *this;
      --position;
      return old;
    };

    // ��=��==
    bool operator!=(const iterator& right) const {
      return position !=
             right.position;  // ָ���ֵ����ֽ�ж��Ƿ�ָ��ͬһ����ַ
    };
    bool operator==(const iterator& right) const {
      return position == right.position;
    };

   protected:
    T* position;
  };

  // ADT����
  bool empty() const { return list_size == 0; };  // �ж����Ա��Ƿ�Ϊ��
  int size() const { return list_size; };         // ���Ա�Ԫ�ظ���
  T& get(int the_index) const;              // ��ȡ����Ϊthe_index��Ԫ��
  int indexOf(const T& the_element) const;  // ��ȡelement��һ�γ��ֵ�����
  void erase(int the_index);                // ɾ��
  void insert(int the_index, const T& the_element);  // ����
  void output(std::ostream& out) const;              // �������
  iterator begin() { return iterator(element); };  // ����ָ�����Ԫ�ص�ָ��
  iterator end() {
    return iterator(element + list_size);
  };  // ����ָ���ĩԪ�صĺ�һ��δ֪��ָ��

  // ��������
  int capacity() const { return array_length; };  // ��������

  // meld�������List a��b��Ԫ��
  void meld(const ArrayList<T>& a, const ArrayList<T>& b);

  // split �����������Ա�a��b��a����*this������Ϊż����Ԫ�أ�b����ʣ���Ԫ��
  void split(ArrayList<T>& a, ArrayList<T>& b);

  // reserve �ߵ������˳��
  void reverse();

  // leftshift �������������ƶ�i��λ��
  void leftShift(int leftShiftCount);

 protected:
  void checkIndex(int the_index) const;  // �鿴�����Ƿ�Ϸ��������Ϸ����׳��쳣
  T* element;                            // �������Ա�Ԫ�ص�һά����
  int array_length;                      // һά���������
  int list_size;                         // ���Ա��е�Ԫ�ظ���
};

//���캯��
template <class T>
ArrayList<T>::ArrayList(int initial_capacity) {
  // �жϲ����Ƿ�Ϸ�
  if (initial_capacity < 1) {
    std::ostringstream s;
    s << "Initial capacity = " << initial_capacity << "Must be > 0 ";
    throw IllegalParameterValue(s.str());
  }
  array_length = initial_capacity;
  element = new T[array_length];
  list_size = 0;
};

// ���ƹ��캯��
template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& the_list) {
  array_length = the_list.array_length;  // �ȸ���capacity
  list_size = the_list.list_size;        // ����size
  element = new T[array_length];
  std::copy(the_list.element, the_list.element + list_size,
            element);  // ����element
};

// �鿴��������
template <class T>
void ArrayList<T>::checkIndex(int the_index) const {
  if (the_index < 0 || the_index >= list_size) {
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }
};

// ��ȡ����Ϊthe_index��Ԫ��
template <class T>
T& ArrayList<T>::get(int the_index) const {
  checkIndex(the_index);
  return element[the_index];
};

// ����Ԫ�ص�һ�γ��ֵ�����
template <class T>
int ArrayList<T>::indexOf(const T& the_element) const {
  int the_index = (int)(std::find(element, element + list_size, the_element) -
                        element);  // stl�е�find����
  if (the_index == list_size)
    return -1;  // û�ҵ�����-1
  else
    return the_index;
};

// ɾ��
template <class T>
void ArrayList<T>::erase(int the_index) {
  checkIndex(the_index);
  std::copy(element + the_index + 1, element + list_size, element + the_index);
  element[--list_size]
      .~T();  // --list_size�ó��ȼ�һ�����Ҷ����һ��Ԫ�ص�����������
};

// ����
template <class T>
void ArrayList<T>::insert(int the_index, const T& the_element) {
  if (the_index < 0 ||
      the_index >
          list_size) {  // ˳�������������һ������λ������Ӧ����list_size���������List_size�����ʧ��
    std::ostringstream s;
    s << "index = " << the_index << " size = " << list_size;
    throw IllegalIndex(s.str());
  }

  // �ж��Ƿ��пռ����
  if (list_size == array_length) {
    ChangeLength1D(element, array_length, 2 * array_length);
    array_length *= 2;  // ���鱶��
  }

  //�ƶ�Ԫ�� ʹ��copy_backward:���ұ߿�ʼ����
  std::copy_backward(element + the_index, element + list_size,
                     element + list_size + 1);
  element[the_index] = the_element;
  list_size++;
};

// ��һ�����Ա��������
template <class T>
void ArrayList<T>::output(std::ostream& out) const {
  std::copy(element, element + list_size, std::ostream_iterator<T>(out, " "));
};

// ����<<
template <class T>
std::ostream& operator<<(std::ostream& out, const ArrayList<T>& x) {
  x.output(out);
  return out;
};

// meld
template <typename T>
void ArrayList<T>::meld(const ArrayList<T>& a, const ArrayList<T>& b) {
  // �α�
  int cursor_a = 0;
  int cursor_b = 0;
  int cursor_c = 0;

  array_length = a.list_size + b.list_size;  // ���鳤��
  delete[] element;                          // �������
  element = new T[array_length];             // �����¿ռ�

  while ((cursor_a < a.list_size) && (cursor_b < b.list_size)) {
    if (cursor_a == cursor_b) {                     // ���渴��
      element[cursor_c++] = a.element[cursor_a++];  // ����a��Ԫ��
    } else {
      element[cursor_c++] = b.element[cursor_b++];  // ����b��Ԫ��
    }
  }

  // ����ѭ����֤����һ���Ѿ���������,��֪���ĸ��������ˣ�������copy��������
  // �������Ļ�����֤�����a��b����һ���Ļ�����ѭ����ʱ��b�ǻ���һ��Ԫ��û�и������������Ҳ���ƺ�
  std::copy(a.element + cursor_a, a.element + a.list_size, element + cursor_c);
  cursor_c += (a.list_size - cursor_a);  // ��ĩβ����һ��λ�ã��±꣩
  std::copy(b.element + cursor_b, b.element + b.list_size, element + cursor_c);
  cursor_c += (b.list_size - cursor_b);  // ��ĩ����һ��λ�ã��±꣩
  list_size = cursor_c;

  /*

  // ����std�Ļ�������������ж����
  if (cursor_a ==
      a.list_size)  // ���a���꣬�����������1��a��bͬ����b����һ��û��copy��
                    // 2��b��a�������������ֻcopy b��������
  {
    std::copy(b.element + cursor_b, b.element + b.list_size,
              element + cursor_c);  // ����
    cursor_c += (b.list_size - cursor_b);
    list_size = cursor_c;
    return;
  }
  // aû�����꣬b�Ѿ�����
  std::copy(a.element + cursor_a, a.element + a.list_size, element + cursor_c);
  cursor_c += (a.list_size - cursor_a);
  list_size = cursor_c;
  return;
  
  */
};

template <typename T>  // a��ż��b����
void ArrayList<T>::split(ArrayList<T>& a, ArrayList<T>& b) {
  // ����Ҫȷ��a��b�����鳤��
  // ���list_size%2!=0 ��֤����������Ԫ�أ����һ��Ԫ���±�Ϊż��
  delete[] a.element;  // �������
  delete[] b.element;  // �������
  b.array_length =
      (int)list_size /
      2;  // �������鳤�ȣ�����ȡ��������list_size����������ż����������
  a.array_length = list_size - b.array_length;  // ż�����鳤��
  a.element = new T[a.array_length];
  b.element = new T[b.array_length];

  // �α�
  int cursor_a = 0;
  int cursor_b = 0;
  int cursor_c = 0;
  while ((cursor_a < a.array_length) && (cursor_b < b.array_length)) {
    if (cursor_c % 2 == 0) {  // ż���±�
      a.element[cursor_a++] = element[cursor_c++];
    } else {  // �����±�
      b.element[cursor_b++] = element[cursor_c++];
    }
  }
  // b������a��
  if (cursor_a == a.array_length) {  // a������bʣ�µ���һ���Ž�ȥ
    b.element[cursor_b] = element[cursor_c];
  } else {
    // b������aʣ�µķŽ�ȥ
    a.element[cursor_a] = element[cursor_c];
  }
  a.list_size = a.array_length;
  b.list_size = b.array_length;
};

// reverse
template<typename T>
void ArrayList<T>::reverse() {
  T temp_element;                              // ��ʱ���ڽ����ı���
  for (int i = 0; i < (list_size / 2); i++) {  // ��������Ϊlist_size/2
    temp_element = element[i];
    element[i] = element[list_size - i - 1];  // ����
    element[list_size - i - 1] = temp_element;
  }
};

// leftShift
template <typename T>
void ArrayList<T>::leftShift(int leftShiftCount) {
  // �ж��Ƿ����ƶ�i��λ��
  if (leftShiftCount <= 0) return;  // ���С�ڵ����㣬����
  int newSize = 0;
  if (leftShiftCount < list_size) {        // �������ȫ���Ƶ�
    newSize = list_size - leftShiftCount;  // �µĳ���
    std::copy(element + leftShiftCount, element + list_size, element);  // �ƶ�
  }
  for (int i = newSize; i < list_size; i++) {  // ����
    element[i].~T();
  }
  // ����ɾ����������
  /*
  for (int i = (list_size - 1); i >= (newSize - 1); i--) {
    element[i].~T();
  }
  */
  list_size = newSize;
};