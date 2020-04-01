#pragma once
#include "arrayQueue.h"
#include "myExceptions.h"
// 工序作为一个数据结构
struct task {
  int machine;  // 该工序占用的机器
  int time;     // 完成该工序需要用时
  task(int the_machine = 0, int the_time = 0) {
    machine = the_machine;
    time = the_time;
  }
};

// 任务作为一个数据结构，每个任务都有若干个工序
struct job {
  arrayQueue<task> taskQ;  // 工序序列
  int length;              // 被调度的工序的时间总和
  int arrivalTime;         // 到达当前机器队列的时间
  int id;                  // 任务编号
  job(int the_Id = 0) {
    id = the_Id;
    length = 0;
    arrivalTime = 0;
  };

  void addTask(int the_machine, int the_time) {
    task the_task(the_machine, the_time);
    taskQ.push(the_task);
  };

  int removeNextTask() {  // 删除任务的下一道工序，返回他需要的时间
    int the_time = taskQ.front().time;
    taskQ.pop();
    length += the_time;
    return the_time;
  }
};

// 机器结构
struct machine {
  arrayQueue<job*> jobQ;  // 机器上等待队列
  // 由于每项任务在任何时刻只会在一个机器队列中所以队列长度应该以任务数目为限
  int changeTime;  // 本机器的转换时间
  int totalWait;   // 本机器的总体延时
  int numTasks;    // 本机器处理的工序数量
  job* activeJob;  // 本机器当前处理的任务

  machine() {
    totalWait = 0;
    numTasks = 0;
    activeJob = NULL;
  }
};

// 空闲机器的完成时间被设置为很大的一个数
class eventList {
 public:
  eventList(int the_num_machines, int the_large_time);
  int nextEvenMachine();  // 要触发下一次事件的的机器

  // 返回将要处理下一事件的时间（就是返回机器的结束时间）
  int nextEventTime(int theMachine) { return finishTime[theMachine]; };

  // 设置结束时间
  void setFinishTime(int the_machine, int the_time) {
    finishTime[the_machine] = the_time;
  }
  ~eventList();

 private:
  int* finishTime;  // 完成时间数组
  int numMachines;   // 机器数量
};

eventList::eventList(int the_num_machine, int the_large_time) {
  // 为m台机器，初始化其完成时间
  if (the_num_machine < 1) {
    throw IllegalParameterValue("number of machine nust be >= 1");
  }
  numMachines = the_num_machine;          // 更新机器数量
  finishTime = new int[numMachines + 1];  // m台机器的完成时间

  // 所有机器都空闲，用大的完成时间初始化
  for (int i = 1; i <= numMachines; i++) {
    finishTime[i] = the_large_time;
  }
};

  // 要触发下一次事件的的机器
int eventList::nextEvenMachine() {
  // 返回值是处理下一项工序的机器

  // 寻找完成时间最早的机器,最早完成工序的机器触发下一个事件
  int p = 1;
  int t = finishTime[1];
  for (int i = 2; i <= numMachines; i++) {  // 从所有机器上找结束时间
    if (finishTime[i] < t) {                // 机器i完成时间更早
      p = i;
      t = finishTime[i];
    }
  }
  return p;
};





eventList::~eventList() {}