#pragma once
#include<iostream>
#include "arrayStack.h"
#include "myExceptions.h"

// ȷ�����غ��Ƿ�ɲ���
// ����net[0,��������n-1]�ܽ������������γ�����
// n�ǹܽŸ���
// ��ֵ��ȵ�����Ԫ����һ�����飬������ֵ����ܽź�
bool checkBox(int net[], int n) {
  arrayStack<int> *s = new arrayStack<int>(n);

  // ��˳ʱ��ɨ������
  for (int i = 0; i < n; i++) {
    if (!s->empty()) {  // ���գ�����ܽ�i
      // ���ջ���ܽ̿��Ƿ����γ�����
      if (net[i] == net[s->top()]) {  // ����γ�����
        s->pop();                     // ��ջ
      } else
        s->push(i);  // �����γ����飬��ܽŽ�ջ
    } else {              // ���ջΪ�գ��ܽŽ�ջ
      s->push(i);
    }
  }

  // �Ƿ���ʣ��Ĳ��ɲ��ߵĹܽ�
  if (s->empty()) {
    // û��ʣ��ܽ�
    std::cout << "Switch box is rountable" << std::endl;
    return true;
  }
  // ��ʣ��ܽ�
  std::cout << "Switch box is not rountable" << std::endl;
  return false;
};