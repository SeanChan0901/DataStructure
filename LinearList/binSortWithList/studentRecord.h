#pragma once
#include <string>
#include <iostream>

struct studentRecord {
  int score;          // ����
  std::string* name;  // ���� ��һ��ָ�룡��
  int operator!=(const studentRecord& x) const { return score == x.score; };
  operator int() const { return score; };   // ������ʽ����ת�������int()
};

// ���շ�����������˳�����
std::ostream& operator<<(std::ostream& out, const studentRecord& x) {
  out << x.score << ' ' << *x.name << std::endl;
  return out;
};