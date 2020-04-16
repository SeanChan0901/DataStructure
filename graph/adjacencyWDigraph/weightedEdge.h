#pragma once
#include <iostream>

#include "graph/edge.h"

// 权重边
template <typename T>
class weightedEdge : public edge<T>{
 private:
  int v1;  // 边的一个顶点
  int v2;  // 边的一个顶点
  T w;     // 变得权重
 public:
  weightedEdge(/* args */) {}
  weightedEdge(int theV1, int theV2, T theWeight)
      : v1(theV1), v2(theV2), w(theWeight){};
  ~weightedEdge(){};
  int vertex1() const { return v1; };
  int vertex2() const { return v2; };
  T weight() const { return w; };
  operator T() const { return w; };  // 重载（）
  void output(std::ostream& out) const {
    // 输出边信息
    out << "(" << v1 << ", " << v2 << ", " << w << ")" << std::endl;
  };
};

// 重载输出运算符
template <typename T>
std::ostream& operator<<(std::ostream& out, weightedEdge<T>& x) {
  x.output(out);
  return out;
};