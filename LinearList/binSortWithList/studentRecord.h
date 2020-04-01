#pragma once
#include <string>
#include <iostream>

struct studentRecord {
  int score;          // 分数
  std::string* name;  // 姓名 是一个指针！！
  int operator!=(const studentRecord& x) const { return score == x.score; };
  operator int() const { return score; };   // 重载显式类型转换运算符int()
};

// 按照分数，姓名的顺序输出
std::ostream& operator<<(std::ostream& out, const studentRecord& x) {
  out << x.score << ' ' << *x.name << std::endl;
  return out;
};