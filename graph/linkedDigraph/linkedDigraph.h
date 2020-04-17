#pragma once
#include <iostream>
#include <sstream>

#include "chain/graphChain.h"
#include "chain/myExceptions.h"
#include "graph/edge.h"
#include "graph/graph.h"
#include "graph/vertexIterator.h"
#include "unweightedEdge.h"

class linkedDigraph : public graph<bool> {
 protected:
  int n;                   // 顶点数
  int e;                   // 边数
  graphChain<int> *aList;  // 邻接表
 public:
  linkedDigraph(int numberOfVertices = 0) {
    if (numberOfVertices < 0)
      throw IllegalParameterValue("number of vertices must be >= 0");
    n = numberOfVertices;
    e = 0;
    aList = new graphChain<int>[n + 1];
  };
  ~linkedDigraph() { delete[] aList; };
  void insertEdge(edge<bool> *theEdge);
  void eraseEdge(int i, int j);
  void checkVertex(int theVertex) const;
  int outDegree(int theVertex) const;
  int inDegree(int theVertx) const;
  int degree(int theVertex) const {
    return inDegree(theVertex) + outDegree(theVertex);
  };
  int numberOfVertices() const { return n; };
  int numberOfEdges() const { return e; };
  bool directed() const { return true; };   // 有向tu
  bool weighted() const { return false; };  // 无权图
  void output(std::ostream &out) const;
  bool existsEdges(int i, int j) const {  // 是否存在边
    if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1)
      // 无此边
      return false;
    else
      return true;
  };
  class myIterator : public vertexIterator<bool> {
   protected:
    chainNode<int> *currentNode;  // 邻接节点的位置

   public:
    myIterator(chainNode<int> *theNode) { currentNode = theNode; };
    ~myIterator(){};
    int next() {
      // 返回于currentNode相邻的一个元素，如果没有返回0
      if (currentNode == NULL) return 0;
      int nextVertex = currentNode->element;  // 节点存储者下一个顶点的位置
      currentNode = currentNode->next;
      return nextVertex;
    }
    int next(bool &theWeight) {
      // 返回于currentNode相邻的一个元素，如果没有返回0
      // 边权设为theWeight
      if (currentNode == NULL) return 0;
      int nextVertex = currentNode->element;
      currentNode = currentNode->next;
      return nextVertex;
    };
  };
  myIterator *iterator(int theVertex) {
    checkVertex(theVertex);
    return new myIterator(aList[theVertex].getFirst());
  };
};

// 检查节点
void linkedDigraph::checkVertex(int theVertex) const {
  if (theVertex < 1 || theVertex > n) {
    std::ostringstream s;
    s << "no vertex " << theVertex;
    throw IllegalParameterValue(s.str());
  }
};

// 插入边
void linkedDigraph::insertEdge(edge<bool> *theEdge) {
  int v1 = theEdge->vertex1();
  int v2 = theEdge->vertex2();
  if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
    std::ostringstream s;
    s << "(" << v1 << "," << v2 << ") is not a permissible edge";
    throw IllegalParameterValue(s.str());
  }

  if (aList[v1].indexOf(v2) == -1) {  // 如果边已经存在，那么创建新编
    aList[v1].insert(0, v2);          // 在0位置插入
    e++;
  }
};

// 删除边
void linkedDigraph::eraseEdge(int i, int j) {
  if (i >= 1 && j >= 1 && i <= n && j <= n) {
    if (aList[i].eraseElement(j))  // edge (i,j) 存在的话边数减一
      e--;
  }
};

//  入度
int linkedDigraph::inDegree(int theVertex) const {
  checkVertex(theVertex);
  int sum = 0;
  for (int j = 1; j <= n; j++) {
    if (aList[j].indexOf(theVertex) != (-1)) sum++;
  }
  return sum;
};

// 出度
int linkedDigraph::outDegree(int theVertex) const {
  checkVertex(theVertex);
  return aList[theVertex].size();
};

// 输出图
void linkedDigraph::output(std::ostream &out) const {
  for (int i = 1; i <= n; i++) {
    out << aList[i] << std::endl;
  }
}

// 重载<<
std::ostream &operator<<(std::ostream &out, linkedDigraph &x) {
  x.output(out);
  return out;
};