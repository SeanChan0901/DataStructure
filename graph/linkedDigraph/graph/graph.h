#pragma once
#include "edge.h"
#include "vertexIterator.h"

// 抽象数据类型
template <typename T>
class graph {
 public:
  virtual ~graph() {}

  // ADT 方法
  virtual int numberOfVertices() const = 0;
  virtual int numberOfEdges() const = 0;
  virtual bool existsEdges(int, int) const = 0;
  virtual void insertEdge(edge<T>*) = 0;
  virtual void eraseEdge(int, int) = 0;
  virtual int degree(int) const = 0;
  virtual int inDegree(int) const = 0;
  virtual int outDegree(int) const = 0;

  // 其他方法
  virtual bool directed() const = 0;  // 当且仅当有向图时，返回值是true
  virtual bool weighted() const = 0;  // 当且仅当加权图时，返回值是true
  virtual vertexIterator<T>* iterator(int) = 0;  // 访问指定顶点的相邻定点
};