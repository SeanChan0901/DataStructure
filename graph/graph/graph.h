#pragma once
#include <iostream>

#include "ArrayList/ArrayList.h"
#include "arrayQueue/arrayQueue.h"
#include "arrayStack/arrayStack.h"
#include "binNode.h"
#include "edge.h"
#include "myExceptions.h"
#include "vertexIterator.h"
#include "weightedEdge.h"

// 抽象数据类型(类型T的边权)
template <typename T>
class graph {
 protected:
  // 变量
  static int *reach;  // 状态判断数组
  static int *path;   // 路径
  static int label;   // 已经访问的标记
  static int length;  // 路径长度
  static int destination;
  static int *bin;       // 指向箱子中的第一个节点
  static binNode *node;  //

  // 方法
  void rDfs(int v);       // 递归深度优先遍历
  bool rFindPath(int s);  // 递归寻找路径
  void creatBins(int b, int n) {}
  void insertBins(int b, int n) {}
  void moveBins(int bMax, int toBin, int v) {}

 public:
  virtual ~graph() {}

  // ADT 方法
  virtual int numberOfVertices() const = 0;
  virtual int numberOfEdges() const = 0;
  virtual bool existsEdges(int, int) const = 0;
  virtual void insertEdge(edge<T> *) = 0;
  virtual void eraseEdge(int, int) = 0;
  virtual int degree(int) const = 0;
  virtual int inDegree(int) const = 0;
  virtual int outDegree(int) const = 0;

  // 其他方法
  virtual bool directed() const = 0;  // 当且仅当有向图时，返回值是true
  virtual bool weighted() const = 0;  // 当且仅当加权图时，返回值是true
  virtual vertexIterator<T> *iterator(
      int) = 0;  // 访问指定顶点的相邻定点(迭代器)
  virtual void output(std::ostream &) const = 0;     // 输出函数
  virtual void bfs(int v, int reach[], int label);   // 广度优先遍历
  void dfs(int v, int reach[], int label);           // 深度优先遍历
  int *findPath(int theSource, int theDestination);  // 寻找一条路径
  bool connected();  // 判断无向图是否连通图，如果是连通图返回true
};

template <typename T>
void graph<T>::bfs(int v, int reach[], int label) {
  // 广度优先搜索。reach[i]用来标记从顶点v可以到达的所有顶点
  arrayQueue<int> q(10);
  reach[v] = label;  // 访问过的节点标记一下
  q.push(v);
  while (!q.empty()) {
    // 从队列中删除一个标记过的顶点
    int w = q.front();
    q.pop();

    // 标记所有没有达到的邻接于顶点w的顶点
    vertexIterator<T> *iw = iterator(w);
    int u;
    while ((u = iw->next()) != 0) {
      // 访问一个w的一个相邻顶点
      if (reach[u] == 0) {
        // u没有到达过
        q.push(u);
        reach[u] = label;  // 做到达标记
      }
    }
    delete iw;  // 释放迭代器内存空间
  }
};

template <typename T>
void graph<T>::rDfs(int v) {
  // 速度优先递归函数
  reach[v] = label;
  vertexIterator<T> *iv = iterator(v);  // 获取迭代器
  int u;
  while ((u = iv->next()) != 0) {
    // 访问未访问过的邻接节点
    if (reach[u] == 0) {
      // 如果未访问过
      rDfs(u);
    }
  }
  delete iv;  // 释放迭代器
};

template <typename T>
void graph<T>::dfs(int v, int reach[], int label) {
  // 广度优先遍历
  graph<T>::reach = reach;
  graph<T>::label = label;
  rDfs(v);
};

template <typename T>
int *graph<T>::findPath(int theSource, int theDestination) {
  // 寻找一条从theSource到theDestination的路径
  // 路径由一个int型的数组返回，经过的每一个节点都保存在数组里面
  // path[0]存储的是路径长度
  // 如果不存在这样的路径返回NULL
  int n = numberOfVertices();
  path = new int[n + 1];  // 默认0是未经过的路径
  path[1] = theSource;  // 第一个顶点
  length = 1;           //当前的路径长度+1
  destination = theDestination;
  reach = new int[n + 1];
  for (int i = 1; i <= n; i++) {
    reach[i] = 0;
  }

  // 搜索路径
  if (theSource == theDestination || rFindPath(theSource))
    path[0] = length - 1;
  else {
    delete[] path;  // 没有这样的路径
    path = NULL;
  }
  
  delete[] reach;
  return path;
};

template <typename T>
bool graph<T>::rFindPath(int s) {
  // 寻找路径的递归算法，从顶点S开始实行深度优先搜索
  // 顶点s不等于终点
  // 当且仅当一条路径被找到，返回true
  reach[s] = 1;  // 访问当前节点
  vertexIterator<T> *is = iterator(s);
  int u;
  while ((u = is->next()) != 0) {
    // 访问s的邻接顶点
    if (reach[u] == 0) {
      path[++length] = u;  // 把u加入路径
      if (u == destination || rFindPath(u)) return u;
    }
  }
  delete is;  // 释放迭代器
  return false;
};

template <typename T>
bool graph<T>::connected() {
  // 当且仅当是连通图时返回true
  // 判断是否无向图
  if (directed())
    throw undefinedMethod("graph::connected() not defined for directed graphs");

  int n = numberOfVertices();
  reach = new int[n + 1];  // 默认reach[i]=0

  // 给邻接与顶点1的可到达顶点做标记
  dfs(1, reach, 1);

  // 判断是否所有顶点都已经标记
  for (int i = 1; i <= n; i++) {
    if (reach[i] == false) return false;
  }
  return true;
};

template<typename T>
int* graph<T>::reach;

template<typename T>
int graph<T>::label;

template<typename T>
int* graph<T>::path;

template<typename T>
int graph<T>::length;

template<typename T>
int graph<T>::destination;

template<typename T>
int* graph<T>::bin;

template<typename T>
binNode* graph<T>::node;
