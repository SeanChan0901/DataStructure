// 加权有向图的邻接矩阵
#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

#include "chain/graphChain.h"
#include "functionOfArray.h"
#include "graph/graph.h"
#include "graph/vertexIterator.h"
#include "myExceptions.h"

template <typename T>
class adjacencyWDigraph : public graph<T> {
 protected:
  int n;               // 顶点个数
  int e;               // 边的个数
  T** adjancecyArray;  // 进阶数组(存储权重)
  T noEdge;  // 表示不存在的边(权重为noEdge的即不存在的边)
 public:
  adjacencyWDigraph(int numberOfVertices = 0, int theNoEdge = 0) {
    // 构造函数
    if (numberOfVertices < 0)
      throw IllegalParameterValue("Number of vertices must be >= 0");
    n = numberOfVertices;
    e = 0;
    noEdge = theNoEdge;
    make2dArray(adjancecyArray, n + 1, n + 1);  // 创建矩阵

    for (int i = 1; i <= n; i++)
      // 初始化矩阵
      std::fill(adjancecyArray[i], adjancecyArray[i] + n + 1, noEdge);
  }
  ~adjacencyWDigraph() { delete2DArray(adjancecyArray, n + 1); };
  int numberOfVertices() const { return n; };
  int numberOfEdges() const { return e; };
  bool existsEdges(int i, int j) const {
    // 返回值是真当且仅当(i,j)是图的一条边
    if (i < 1 || j < 1 || i > n || j > n || adjancecyArray[i][j] == noEdge)
      return false;
    else
      return true;
  };
  int degree(int) const;
  int inDegree(int) const;
  int outDegree(int) const;
  void insertEdge(edge<T>*);
  void eraseEdge(int, int);
  void checkVertex(int theVertex) const;
  bool directed() const { return true; };  // 当且仅当有向图时，返回值是true
  bool weighted() const { return true; };  // 当且仅当加权图时，返回值是true
  void shorttestPaths(int sourceVertex, T* distanceFromSource,
                      int* predecessor);  // 寻找单源最短路径
  void output(std::ostream& out) const {  // 输出整个邻接矩阵
    for (int i = 1; i <= n; i++) {
      std::copy(adjancecyArray[i] + 1, adjancecyArray[i] + n + 1,
                std::ostream_iterator<T>(out, " "));
      out << std::endl;
    }
  };
  class myIterator : public vertexIterator<T> {
   protected:
    T* row;    // 邻接矩阵的行
    T noEdge;  // theRow[i]==noEdge当且仅当没有关联顶点i的边
    int n;     // 顶点数
    int currentVertex;  // 需要迭代到的下一个位置
                        // 图的迭代器
   public:
    myIterator(T* theRow, T theNoedge, int numberOfVertices) {
      row = theRow;
      noEdge = theNoedge;
      n = numberOfVertices;
      currentVertex = 1;
    };
    ~myIterator(){};

    int next() {
      // 返回下一个顶点，若不存在，返回0
      // 寻找下一个邻接顶点
      for (int j = currentVertex; j <= n; j++)
        if (row[j] != noEdge) {
          currentVertex = j + 1;
          return j;
        }
      // 不存在下一个邻接的顶点了
      currentVertex = n + 1;  // 配合checkVertex使用
      return 0;
    };

    int next(T& theWeight) {
      // 返回下一个顶点，若不存在，返回0
      // 令其与下一个顶点的边的权值赋给theWeight
      // 寻找下一个邻接顶点
      for (int j = currentVertex; j <= n; j++)
        if (row[j] != noEdge) {
          currentVertex = j + 1;
          theWeight = row[j];
          return j;
        }
      // 不存在下一个邻接的顶点了
      currentVertex = n + 1;  // 配合checkVertex使用
      return 0;
    };
  };
  myIterator* iterator(int theVertex) {
    // 返回顶点theVertex的迭代器
    checkVertex(theVertex);
    return new myIterator(adjancecyArray[theVertex], noEdge, n);
  };
};

template <typename T>
void adjacencyWDigraph<T>::insertEdge(edge<T>* theEdge) {
  // 插入边，如果边已存在，那么覆盖他
  int v1 = theEdge->vertex1();
  int v2 = theEdge->vertex2();

  if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
    std::ostringstream s;
    s << "(" << v1 << ", " << v2 << ")"
      << " is not a permissible edge";
    throw IllegalParameterValue(s.str());
  }

  if (adjancecyArray[v1][v2] == noEdge)
    // 新边插入
    e++;
  adjancecyArray[v1][v2] = theEdge->weight();
};

template <typename T>
void adjacencyWDigraph<T>::eraseEdge(int i, int j) {
  // 删除边(i,j)
  if (i >= 1 && j >= 1 && i != j && i <= n && j <= n &&
      adjancecyArray[i][j] != noEdge) {
    adjancecyArray[i][j] = noEdge;
    std::cout << "after erase , a[i][i] = " << adjancecyArray[i][j]
              << std::endl;
    e--;
  }
};

template <typename T>
void adjacencyWDigraph<T>::checkVertex(int theVertex) const {
  // 确认是有效顶点
  if (theVertex < 1 || theVertex > n) {
    std::ostringstream s;
    s << "no vertex : " << theVertex;
    throw IllegalParameterValue(s.str());
  }
};

// 顶点的度
template <typename T>
int adjacencyWDigraph<T>::degree(int theVertex) const {
  // 如果是有向图的话可以不写这个函数
  return inDegree(theVertex) + outDegree(theVertex);
};

// 顶点的入度
template <typename T>
int adjacencyWDigraph<T>::inDegree(int theVertex) const {
  checkVertex(theVertex);

  // 计算关联至theVertex的边数
  int sum = 0;
  for (int j = 1; j <= n; j++)
    if (adjancecyArray[j][theVertex] != noEdge) sum++;

  return sum;
};

// 顶点的出度
template <typename T>
int adjacencyWDigraph<T>::outDegree(int theVertex) const {
  checkVertex(theVertex);

  // 计算关联至theVertex的边数
  int sum = 0;
  for (int j = 1; j <= n; j++)
    if (adjancecyArray[theVertex][j] != noEdge) sum++;

  return sum;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, adjacencyWDigraph<T>& x) {
  x.output(out);
  return out;
};

template <typename T>
void adjacencyWDigraph<T>::shorttestPaths(int sourceVertex,
                                          T* distanceFromSource,
                                          int* predecessor) {
  // 寻找从源sourceVertex开始的最短路径
  // 在数组distanceFromSource中返回最短路径
  // 在数组predecessor中返回顶点在路径上的前驱
  if (sourceVertex < 1 || sourceVertex > n)
    throw IllegalParameterValue("Invalid source vertex");

  // 确认*this是加权图
  if (!weighted())
    throw undefinedMethod(
        "adjacencyWDigraph::shortestPaths() not defined for unweighted graphs");

  graphChain<int> newReachableVertices;

  // 初始化
  for (int i = 1; i <= n; i++) {
    distanceFromSource[i] =
        adjancecyArray[sourceVertex][i];  // 与源点邻接的点与源点的距离
    if (distanceFromSource[i] == noEdge)
      predecessor[i] = -1;  // 如果不与源点邻接，则其前驱设为-1
    else {
      predecessor[i] = sourceVertex;  //与源点邻接的其前驱设为源点
      newReachableVertices.insert(0, i);  // 把他放入可到达顶点集中
    }
  }
  distanceFromSource[sourceVertex] = 0;  // 到达其自身的平凡路径长度设为0
  predecessor[sourceVertex] = 0;         // 源点没有前驱

  // 更新distanceFromSource
  while (!newReachableVertices.empty()) {
    // 存在更多的路径
    // 寻找distanceFromSource最小的，还未在顶点集中的顶点v
    chain<int>::iterator iNewReachableVertices =
        newReachableVertices.begin();  // 获取链表的迭代器
    chain<int>::iterator theEnd = newReachableVertices.end();  // 链表末
    int v =
        *iNewReachableVertices;  // 获取当前迭代器位置的节点的元素值(也就是邻接的顶点)
    iNewReachableVertices++;  // 迭代到下一个位置
    while (iNewReachableVertices != theEnd) {
      int w = *iNewReachableVertices;
      iNewReachableVertices++;
      if (distanceFromSource[w] < distanceFromSource[v])
        v = w;  // 找距离源点最近的点，令成v
    }

    // 下一条最短路径是到达顶点v
    // 从newReachableVertices删除顶点v，然后更新distanceFromSource
    newReachableVertices.eraseElement(v);
    for (int j = 1; j <= n; j++) {
      if (adjancecyArray[v][j] != noEdge &&
          (predecessor[j] == -1 ||
           distanceFromSource[j] >
               (distanceFromSource[v] + adjancecyArray[v][j]))) {
        // 更新最短路径
        distanceFromSource[j] = distanceFromSource[v] + adjancecyArray[v][j];
        // 把顶点j驾到newReachableVertices中去
        if (predecessor[j] == -1) newReachableVertices.insert(0, j);
        predecessor[j] = v;
      }
    }
  }
}