#include <iostream>
#include "maxHblt.h"

using namespace  std;

int main(){
    int *intElement=new int[6];
    intElement[1]=7;
    intElement[2]=1;
    intElement[3]=9;
    intElement[4]=11;
    intElement[5]=2;

    maxHblt<int> aMaxHblt;
    aMaxHblt.initialize(intElement,5);
    aMaxHblt.output();
    return 0;
}
