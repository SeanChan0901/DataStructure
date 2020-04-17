#pragma once
#include<iostream>
#include "arrayStack.h"
#include "myExceptions.h"

// 确定开关盒是否可布线
// 数组net[0,····n-1]管脚组数，用以形成网组
// n是管脚个数
// 即值相等的两个元素是一个网组，其索引值代表管脚号
bool checkBox(int net[], int n) {
  arrayStack<int> *s = new arrayStack<int>(n);

  // 按顺时针扫描数组
  for (int i = 0; i < n; i++) {
    if (!s->empty()) {  // 不空，处理管脚i
      // 检查栈顶管教看是否能形成网组
      if (net[i] == net[s->top()]) {  // 如果形成网组
        s->pop();                     // 出栈
      } else
        s->push(i);  // 不能形成网组，则管脚进栈
    } else {              // 如果栈为空，管脚进栈
      s->push(i);
    }
  }

  // 是否有剩余的不可布线的管脚
  if (s->empty()) {
    // 没有剩余管脚
    std::cout << "Switch box is rountable" << std::endl;
    return true;
  }
  // 有剩余管脚
  std::cout << "Switch box is not rountable" << std::endl;
  return false;
};