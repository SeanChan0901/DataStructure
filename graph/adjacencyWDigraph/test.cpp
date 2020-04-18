#include "adjacencyWDigraph.h"
#include "weightedEdge.h"

using namespace std;

int main() {
  // insert
  adjacencyWDigraph<int> a_adWDgraph(6, -1);
  edge<int>* a_wEdge = new weightedEdge<int>(1, 3, 10);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(1, 4, 6);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(2, 4, 1);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(2, 5, 3);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(3, 6, 7);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(4, 6, 10);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(5, 6, 15);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  cout << a_adWDgraph << endl;

  int n = a_adWDgraph.numberOfVertices();
  int topologicalOrder[n];
  if (a_adWDgraph.topologicalOrder(topologicalOrder)) {
    cout << " exsit topological order" << endl;
    for (int i = 0; i < n; i++) cout << topologicalOrder[i] << " ";
    cout << endl;
  }

  // erase
  /*
  a_adWDgraph.eraseEdge(1, 3);
  cout << a_adWDgraph << endl;
  cout << a_adWDgraph.outDegree(1) << endl;
  cout << a_adWDgraph.inDegree(1) << endl;
  */

  // bfs
  int bfsReach[n + 1];
  for (int i = 0; i < n + 1; i++) bfsReach[i] = 0;
  a_adWDgraph.bfs(2, bfsReach, 999);
  for (int i = 1; i <= n; i++) cout << bfsReach[i] << " ";
  cout << endl;

  // dfs
  int dfsReach[n + 1];
  for (int i = 0; i < n + 1; i++) dfsReach[i] = 0;
  a_adWDgraph.dfs(2, dfsReach, 999);
  for (int i = 1; i <= n; i++) cout << dfsReach[i] << " ";
  cout << endl;

  // shortestPaths
  adjacencyWDigraph<int> b_adWDgraph(5, -1);
  edge<int>* b_wEdge = new weightedEdge<int>(1, 2, 4);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(1, 3, 2);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(1, 5, 8);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(2, 5, 5);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(2, 4, 4);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(3, 4, 1);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  b_wEdge = new weightedEdge<int>(4, 5, 3);
  b_adWDgraph.insertEdge(b_wEdge);
  delete b_wEdge;
  cout << b_adWDgraph << endl;

  int m = b_adWDgraph.numberOfVertices();
  int disFromS[m + 1];
  int predecessor[m + 1];
  b_adWDgraph.shorttestPaths(1, disFromS, predecessor);
  for (int i = 1; i <= m; i++) {
    cout << predecessor[i] << " ";
  }
  cout << endl;
  return 0;
};