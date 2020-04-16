#include "adjacencyWDigraph.h"
#include "weightedEdge.h"

using namespace std;

int main() {
  adjacencyWDigraph<int> a_adWDgraph(4, -1);
  edge<int>* a_wEdge = new weightedEdge<int>(1, 4, 10);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(1, 2, 5);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(1, 3, 6);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(2, 3, 1);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(2, 1, 3);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(3, 2, 7);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(3, 4, 10);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(3, 1, 15);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(4, 1, 11);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  a_wEdge = new weightedEdge<int>(4, 3, 12);
  a_adWDgraph.insertEdge(a_wEdge);
  delete a_wEdge;
  cout << a_adWDgraph << endl;
  return 0;
};