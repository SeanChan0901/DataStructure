#pragma once
#include <algorithm>
#include <numeric>

struct equivNode {
  int equivClass;  // Ԫ�����ͱ�ʶ��(�ȼ���ı�ʶ��)
  int size;  //  �ȼ�����Ԫ�صĸ���
  int next;  // �ȼ����е�Ԫ��ָ����һ��Ԫ�ص�ָ�� 
};

equivNode *node;
int n;

void initialize(int numberOfElements) {
  // ��ÿ�����Ԫ�س�ʼ��numberOfelements����
  n = numberOfElements;
  node = new equivNode[n + 1];

  for (int e = 0; e <= n; e++) {
    node[e].equivClass = e;  // �ȼ�������Ϊe
    node[e].next = 0;  // �ȼ�����ֻ��һ��Ԫ��
    node[e].size = 1;  // 
  }
};

void unite(int class_a, int class_b) {
  // �ϲ���a����b
  // ������a��b���ǵȼ���
  // class_a �� class_b�ǵȼ���ı���Ԫ��

  // ʹa��Ϊ��С���Ǹ��ȼ���
  if (node[class_a].size > node[class_b].size) {
    std::swap(class_a, class_b);
  }

  // �ı��С���equivClass��ֵ
  int k;
  // �ı�ȼ���aԪ���е����ʶ�������ҵ��ȼ���a�����һ��Ԫ��
  for (k = class_a; node[k].next != 0; k = node[k].next) {
    node[k].equivClass = class_b;  // �ȼ����ǩ�ĳ�b
  }
  node[k].equivClass = class_b;  // ��������һ���ڵ�

  node[class_b].size += node[class_a].size;  // size���
  node[k].next = node[class_b].next;  // aĩβ�ӵ�b�ĵڶ���Ԫ��ǰ
  node[class_b].next = class_a;       // b�ĵ�һ��Ԫ����aͷ����
  // �������仰������������classBԪ��֮���������classA
};

int find(int the_element) { return node[the_element].equivClass; };
