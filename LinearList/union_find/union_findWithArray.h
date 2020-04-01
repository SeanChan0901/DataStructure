#pragma once
#include <iostream>

int *equivClass, n;
void initialize(int numberOfElements) {
  // ��ÿ�����һ��Ԫ�س�ʼ��numbersOfElements����
  n = numberOfElements;
  equivClass = new int[n + 1];  // ��ô��������ĵȼ���
  for (int e = 1; e <= n; e++) {
    equivClass[e] = e;
  }
}

// ������ǵȼ���
void unite(int class_a, int class_b) {
  // �ϲ���a��b
  // ������A��B���ȼ�
  for (int k = 1; k <= n; k++) {  // ��������Ԫ�أ�
    if (equivClass[k] == class_b) {  // ������ô����ȼ������棬����b�ȼ۵�
      equivClass[k] = class_a;  // �ϲ�a��b����ȼ���b�е�����Ԫ�����͵���a
    }
  }
};

int find(int the_element) {  // ��ĳ��Ԫ�صĵȼ���
  return equivClass[the_element];
};