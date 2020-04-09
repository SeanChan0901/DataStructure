#pragma once
#include <iostream>

#include "lptNodes.h"
#include "maxHeap.h"
#include "minHeap.h"

// 输入作业，作业数量，机器数量
void makeSchedule(jobNode jobs[], int n, int m) {
  // 输出一个基于n个作业jobs[1:n]的m台机器的LPT调度

  // 作业数小于机器数，不需要调度
  if (n <= m) {
    std::cout << "Schedule each job on a different machine." << std::endl;
    return;
  }

 heapSort(jobs, n);  // 堆排序(递增)

  // 初始化m台机器，建立小根堆
  minHeap<machineNode> machineHeap(m);
  for (int i = 1; i <= m; i++) {
    machineHeap.push(machineNode(i, 0));
  }

  // 生成调度计划
  for (int i = n; i >= 1; i--) {
    // 把作业i安排在第一台空闲机器
    machineNode x = machineHeap.top();
    machineHeap.pop();
    std::cout << "Schudule job " << jobs[i].id << " on machin " << x.id
              << " from " << x.avail << " to " << x.avail + jobs[i].time
              << std::endl;
    x.avail += jobs[i].time;
    machineHeap.push(x);
  }
};