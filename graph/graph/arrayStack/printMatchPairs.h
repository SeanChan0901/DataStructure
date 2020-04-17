#pragma once
#include "arrayStack.h"
#include <iostream>
#include <string>
#include "myExceptions.h"

// 表达式括号匹配
void printMatchPairs(std::string expression) {
  arrayStack<int> s;  // int类型记录的是左括号在表达式中的位置
  int length = (int)expression.size();

  // 扫描表达式expression 寻找左括号和右括号
  for (int i = 0; i < length; i++) {
    if (expression.at(i) == '(') {  // 如果找到左括号，压入栈
      s.push(i);
    } else {
      if (expression.at(i) ==
          ')') {  // 如果找到右括号，那么匹配最近入栈的左括号
        try {
          std::cout << s.top() << ' ' << i << std::endl;  // s.top()是左括号位置，i是右括号位置
          s.pop();                //
        } catch (stackEmpty()) {  // 没有括号匹配
          std::cout << "No match for right paranthesis"
                    << " at" << i
                    << std::endl;  // i位置上的右括号没又匹配的左括号
        }
      }
    }
  }
  // 栈不为空则剩余在栈中的左括号是不匹配的
  while (!s.empty()) {
    std::cout << "No match for left paranehesis at" << s.top() << std::endl;
    s.pop();
  }
};