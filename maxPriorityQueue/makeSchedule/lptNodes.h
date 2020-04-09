#pragma once
#include <iostream>

class jobNode {
  // 友元函数
  friend void makeSchedule(jobNode *, int, int);
  friend int main();

 public:
  operator int() const { return time; }

 private:
  int id,    // 作业id
      time;  // 作业处理时间
};

class machineNode {
  friend void makeSchedule(jobNode *, int, int);

 public:
  machineNode(int theID = 0, int theAvail = 0) {
    id = theID;
    avail = theAvail;
  }
  operator int() const { return avail; }

 private:
  int id,     // 机器id
      avail;  // 机器空闲时刻
};
