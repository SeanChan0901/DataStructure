#pragma once
#include <algorithm>
#include <numeric>

struct equivNode {
  int equivClass;  // 元素类型标识符(等价类的标识符)
  int size;  //  等价类中元素的个数
  int next;  // 等价类中的元素指向下一个元素的指针 
};

equivNode *node;
int n;

void initialize(int numberOfElements) {
  // 用每个类的元素初始化numberOfelements个类
  n = numberOfElements;
  node = new equivNode[n + 1];

  for (int e = 0; e <= n; e++) {
    node[e].equivClass = e;  // 等价类类型为e
    node[e].next = 0;  // 等价类中只有一个元素
    node[e].size = 1;  // 
  }
};

void unite(int class_a, int class_b) {
  // 合并类a和类b
  // 假设类a和b不是等价类
  // class_a 和 class_b是等价类的表首元素

  // 使a成为较小的那个等价类
  if (node[class_a].size > node[class_b].size) {
    std::swap(class_a, class_b);
  }

  // 改变较小类的equivClass的值
  int k;
  // 改变等价类a元素中的类标识符，并找到等价类a中最后一个元素
  for (k = class_a; node[k].next != 0; k = node[k].next) {
    node[k].equivClass = class_b;  // 等价类标签改成b
  }
  node[k].equivClass = class_b;  // 链表的最后一个节点

  node[class_b].size += node[class_a].size;  // size相加
  node[k].next = node[class_b].next;  // a末尾接到b的第二个元素前
  node[class_b].next = class_a;       // b的第一个元素与a头接上
  // 以上两句话的作用是链表classB元素之后插入链表classA
};

int find(int the_element) { return node[the_element].equivClass; };
