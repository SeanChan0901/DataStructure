#include <iostream>

#include "uniteFindWithTreeArray.h"
#include "uniteFindWithTreeWight.h"
using namespace std;
int main() {
  uniteFindWithTreeArray::initialize(10);
  uniteFindWithTreeArray::unite(1, 2);
  uniteFindWithTreeArray::unite(3, 4);
  uniteFindWithTreeArray::unite(1, 3);
  cout << "find(1) = " << uniteFindWithTreeArray::find(1)
       << " find(2) = " << uniteFindWithTreeArray::find(2) << endl;
  cout << "find(3) = " << uniteFindWithTreeArray::find(3)
       << " find(4) = " << uniteFindWithTreeArray::find(4) << endl;
  cout << "find(5) = " << uniteFindWithTreeArray::find(5)
       << " find(6) = " << uniteFindWithTreeArray::find(6) << endl
       << endl
       << endl;
  uniteFindWithTreeWeight::initialize(10);
  uniteFindWithTreeWeight::unite(1, 2);
  uniteFindWithTreeWeight::unite(3, 4);
  uniteFindWithTreeWeight::unite(1, 3);
  cout << "find(1) = " << uniteFindWithTreeWeight::find(1)
       << " find(2) = " << uniteFindWithTreeWeight::find(2) << endl;
  cout << "find(3) = " << uniteFindWithTreeWeight::find(3)
       << " find(4) = " << uniteFindWithTreeWeight::find(4) << endl;
  cout << "find(5) = " << uniteFindWithTreeWeight::find(5)
       << " find(6) = " << uniteFindWithTreeWeight::find(6) << endl;
  return 0;
}