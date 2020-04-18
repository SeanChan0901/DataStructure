#pragma once
#include <algorithm>
#include <iostream>

#include "ArrayList/ArrayList.h"
#include "arrayQueue/arrayQueue.h"
#include "arrayStack/arrayStack.h"
#include "binNode.h"
#include "edge.h"
#include "fastUnionFind.h"
#include "minHeap/minHeap.h"
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
  int lableComponents(int c[]);                      // 标记构件
  bool topologicalOrder(int *theOrder);              // 拓扑排序
  bool kruskal(weightedEdge<T> *spanningTreeEdges);  // kruskal算法
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
  path[1] = theSource;    // 第一个顶点
  length = 1;             //当前的路径长度+1
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

template <typename T>
int graph<T>::lableComponents(int c[]) {
  // 给无向图的标记构件
  // 返回构件的个数
  // 令c[i]是顶点i的构件号

  //  确定是一个无向图
  if (directed())
    throw undefinedMethod(
        "graph::labelComponents() not defined for directed graphs");

  int n = numberOfVertices();

  // 令所有顶点是非构件
  for (int i = 1; i <= n; i++) c[i] = 0;

  label = 0;  // 最后一个构件的编号
  // 确定构件
  // 每一个构件都用一次广度遍历（用深度遍历也可以）
  for (int i = 1; i <= n; i++)
    if (c[i] == 0) {
      // 顶点i未到达
      // 顶点i是一个新构件
      label++;
      bfs(i, c, label);
    }

  return label;
};

template <typename T>
bool graph<T>::topologicalOrder(int *theOrder) {
  // 返回false当且仅当图没有拓扑序列（有环）
  // 如果存在一个拓扑序列，将其赋给theOrder[0:n-1]

  // 确定有向图
  if (!directed())
    throw undefinedMethod(
        "graph::topologicalOrder() not defined for undirected graphs");

  int n = numberOfVertices();

  // 计算入度
  int *inDegree = new int[n + 1];
  std::fill(inDegree, inDegree + n + 1, 0);

  // 初始化图的所有入度
  for (int i = 1; i <= n; i++) {
    // 顶点i的出边
    vertexIterator<T> *ii = iterator(i);
    int u;
    while ((u = ii->next()) != 0)
      // 访问i的邻接点
      inDegree[u]++;
  }

  // 把入度为0的顶点加入栈中
  arrayStack<int> stack;
  for (int i = 1; i <= n; i++)
    if (inDegree[i] == 0) stack.push(i);

  // 生成拓扑序列
  int j = 0;  // 数组theOrder的索引
  while (!stack.empty()) {
    // 从栈中提取顶点
    int nextVertexInTopolocicalOrder = stack.top();
    stack.pop();
    theOrder[j++] = nextVertexInTopolocicalOrder;

    // 更新入度
    vertexIterator<T> *iNextVertex = iterator(nextVertexInTopolocicalOrder);
    int u;
    while ((u = iNextVertex->next()) != 0) {
      inDegree[u]--;
      if (inDegree[u] == 0) stack.push(u);
    }
  }
  delete[] inDegree;
  return (j == n);
};

template <typename T>
bool graph<T>::kruskal(weightedEdge<T> *spanningTreeEdges) {
  // 使用kruskal方法生成一棵最小生成树
  // 返回false当且仅当加权无向图是不连通的
  // 算法结束时，spanningTreeEdge：[0:n-2]存储的是最小生成树的边(共n-1条)

  // 确定是否带权无向图
  if (directed() || !weighted())
    throw undefinedMethod(
        "graph::kruskal() not defined for unweighted and directed graphs");

  int n = numberOfVertices();
  int e = numberOfEdges();

  // 建立一个数组用来存储边集
  weightedEdge<T> *edge = new weightedEdge<T>[e + 1];
  int k = 0;  // 数组edge的索引
  for (int i = 1; i <= n; i++) {
    // 取所有关联到i的边
    vertexIterator<T> *ii = iterator(i);  // 迭代器
    int j;                                // 下一个邻接点
    T w;                                  // 存储边的权值
    while ((j = ii->next(w)) != 0)
      if (i < j)  // 向数组添加一条,
        // 确保(无向图确保i->j和j->i是同一条边，不会重复添加）
        edge[++k] = weightedEdge<T>(i, j, w);
  }

  // 把边插入小根堆
  minHeap<weightedEdge<T> > heap(1);
  heap.initialize(edge, e);

  fastUnionFind uf(n);

  // 按照权的递增顺序提取边
  k = 0;  // 用于存储索引
  while (e > 0 && k < n - 1) {
    // 生成树没有完成且还有边存在
    weightedEdge<T> x = heap.top();
    heap.pop();
    e--;
    int a = uf.find(x.vertex1());  // 边对应其中一个顶点的类别
    int b = uf.find(x.vertex2());  // 同上

    if (a != b) {
      // 不是同一个等价类：加入最小生成树边集
      spanningTreeEdges[k++] = x;
      uf.unite(a, b);
    }
  }
  return (k == (n - 1));
};

template <typename T>
int *graph<T>::reach;

template <typename T>
int graph<T>::label;

template <typename T>
int *graph<T>::path;

template <typename T>
int graph<T>::length;

template <typename T>
int graph<T>::destination;

template <typename T>
int *graph<T>::bin;

template <typename T>
binNode *graph<T>::node;
