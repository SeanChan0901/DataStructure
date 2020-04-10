#pragma once

struct binType {
  int unusedCapacity;

  bool operator<=(binType& right) const {
    return (unusedCapacity >= right.unusedCapacity) ? true : false;
  }
};
