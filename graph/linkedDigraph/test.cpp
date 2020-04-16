#include <iostream>

#include "linkedDigraph.h"
using namespace std;

int main() {
  linkedDigraph alinkedDigraph(4);
  unweightedEdge e[10] = {unweightedEdge(1, 4), unweightedEdge(1, 2),
                          unweightedEdge(1, 3), unweightedEdge(2, 3),
                          unweightedEdge(2, 1), unweightedEdge(3, 2),
                          unweightedEdge(3, 4), unweightedEdge(3, 1),
                          unweightedEdge(4, 1), unweightedEdge(4, 3)};
  unweightedEdge *uwe;
  for (int i = 0; i < 10; i++) {
    uwe = &e[i];
    alinkedDigraph.insertEdge(uwe);
  }
  cout << alinkedDigraph << endl;
  uwe=&(e[0]);
  alinkedDigraph.eraseEdge(1,3);
  cout<<alinkedDigraph<<endl;
  return 0;
}