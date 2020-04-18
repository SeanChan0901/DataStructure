#ifndef LinearList_
#define LinearList_
#include <iostream>

template <class T>
class LinearList {  // ���Ա��˳���ʵ�֣�����ʵ�֣�
 public:
  virtual ~LinearList(){};  // ������������Ϊ�麯��ʹ�ö����ܹ��ҵ��Լ������������
  virtual bool empty() const = 0;           // �Ƿ�Ϊ�գ����򷵻�true
  virtual int size() const = 0;             // �������Ա�Ԫ�ظ���
  virtual T& get(int the_index) const = 0;  // ����������Ӧ��Ԫ��
  virtual int indexOf(
      const T& the_element) const = 0;  // ����Ԫ�ص�һ�γ��ֵ�����ֵ
  virtual void erase(int the_index) = 0;  // ɾ������Ϊthe_index��Ԫ��
  virtual void insert(
      int the_index,
      const T&
          the_element) = 0;  // ��Ԫ��the_element���뵽����the_index��λ����
  virtual void output(std::ostream& out) const = 0;  // �����Ա���������
};

#endif