#pragma once
#include "arrayStack.h"
#include <iostream>
#include <string>
#include "myExceptions.h"

// ���ʽ����ƥ��
void printMatchPairs(std::string expression) {
  arrayStack<int> s;  // int���ͼ�¼�����������ڱ��ʽ�е�λ��
  int length = (int)expression.size();

  // ɨ����ʽexpression Ѱ�������ź�������
  for (int i = 0; i < length; i++) {
    if (expression.at(i) == '(') {  // ����ҵ������ţ�ѹ��ջ
      s.push(i);
    } else {
      if (expression.at(i) ==
          ')') {  // ����ҵ������ţ���ôƥ�������ջ��������
        try {
          std::cout << s.top() << ' ' << i << std::endl;  // s.top()��������λ�ã�i��������λ��
          s.pop();                //
        } catch (stackEmpty()) {  // û������ƥ��
          std::cout << "No match for right paranthesis"
                    << " at" << i
                    << std::endl;  // iλ���ϵ�������û��ƥ���������
        }
      }
    }
  }
  // ջ��Ϊ����ʣ����ջ�е��������ǲ�ƥ���
  while (!s.empty()) {
    std::cout << "No match for left paranehesis at" << s.top() << std::endl;
    s.pop();
  }
};