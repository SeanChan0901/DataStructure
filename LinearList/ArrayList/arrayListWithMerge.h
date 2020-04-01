#pragma once
#include <algorithm>
#include <numeric>
#include "ArrayList.h"

// �����
template <typename T>
class arrayListWithMerge : public ArrayList<T> {
 public:
  // ���캯����ArrayListһ��
  arrayListWithMerge(int initial_capacity = 10)
      : ArrayList<T>(initial_capacity){};
  ~arrayListWithMerge() {}

  // �ϲ�
  void merge(const arrayListWithMerge<T>& a, const arrayListWithMerge<T>& b);
};

// �̳й�����protectedΪʲôҪ��thisָ�������ʣ�
// ��C++�̳�ģ���࣬��Ҫʹ��thisָ�����Base::���ó�Ա����
// ��C++�����������ģ���ֱ࣬�ӵ��ø����Ա�Ļ����ᱨ���Ҳ����ñ����������ԭ������Ϊģ��Ķ��α�����Ƶ��µġ�

//
template <typename T>
void arrayListWithMerge<T>::merge(const arrayListWithMerge<T>& a,
                                  const arrayListWithMerge<T>& b) {
  int cursor_a = 0;  // a����α�
  int cursor_b = 0;  // b����α�
  int cursor_c = 0;  // c����α�

  // �ڿ�ʼ����֮ǰ�����ͷź��Ѿ�������ڴ�ռ�
  delete[] this->element;
  this->array_length = a.list_size + b.list_size;  // ��Ա�������Է���˽�г�Ա
  this->element = new T[this->array_length];             // �����µ��ڴ�ռ�

  // merge a��b
  while ((cursor_a < a.list_size) &&
         (cursor_b < b.list_size)) {  // ����������û������
    if (a.element[cursor_a] <= b.element[cursor_b]) {  // a���е�Ԫ�ر�b��С
      this->element[cursor_c++] =
          a.element[cursor_a++];  // a����Ԫ�ظ��Ƶ��±�a���±��α����һλ
    } else {                    // ���b����Ԫ�ر�a���е�С
      this->element[cursor_c++] =
          b.element[cursor_b++];  // b���е�Ԫ�ظ��Ƶ��±�b���±��α����һλ
    }
  }  // �Ƴ�ѭ����������һ����Ԫ���Ѿ��������ˣ��п���������ȳ�ͬʱ�����꣩
  // ѭ���������±���α�cursor_c�����һ��Ԫ�ص���һ��λ��
  // ��û�и�����ı��ʣ���Ԫ�ؼӵ��±���
  std::copy(a.element + cursor_a, a.element + a.list_size, this->element + cursor_c);
  //  ���a���Ƶ��±�cursor_aʱ��û�����꣬��ô�ʹ����￪ʼ����ʣ�µ�Ԫ�أ�
  //  ����Ѿ������꣬������ô���Ḵ���κζ���
  //  ���Ƶ�Ԫ�ظ���Ϊ a.list_size-cursor_a
  cursor_c += (a.list_size - cursor_a);  // ��ʱcursor�Ѿ��Ƶ�һ���µ�λ��
  // ��Ŀǰ���һ��Ԫ�ص���һ��λ�ã�׼����һ�ο���
  std::copy(b.element + cursor_b, b.element + b.list_size, this->element + cursor_c);
  cursor_c += (b.list_size - cursor_b);

  this->list_size = cursor_c;  // �պ���list_size��Ŀǰ���һ��Ԫ�ص���һ��λ�ã�
};