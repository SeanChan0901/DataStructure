// machineShopSimulator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "struture.h"
#include "functionfOfArray.h"
#include "myExceptions.h"
using namespace std;

// 全局变量
int time_now;  // 当前时间（单位）
int num_machines;  // 机器数量
int num_jobs;  // 任务数量
eventList* e_list;  // 事件表的指针
machine* m_array;  // 机器数组
int largeTime = 10000;  // 在这个事件之前所有机器都已经完成工序

void inputData() {
  // 输入工厂数据

  cout << "Enter number of machines and jobs" << endl;
  cin >> num_machines >> num_jobs;
  if (num_machines < 1 || num_jobs < 1) {
    throw IllegalInputData("number of machines and jobs must be >= 1");
  }

  // 生成事件和机器队列
  e_list = new eventList(num_machines, largeTime);  // m个机器，全部处于空闲状态
  m_array = new machine[num_machines + 1];  // 机器数组

  // 输入机器的转换时间
  cout << "enter change_over times for machines" << endl;
  int ct;
  for (int j = 1; j <= num_machines; j++) {
    cin >> ct;
    if (ct < 0) throw IllegalInputData("change_over times must be > 0");
    m_array[j].changeTime = ct;
  }

  //输入任务
  job* the_job;
  int num_tasks, first_machine, the_machine, the_task_time;
  for (int i = 1; i <= num_jobs; i++) {
    cout << "Enter number of tasks for the job " << i << endl;
    cin >> num_tasks;
    first_machine = 0;
    if (num_tasks < 1) {
      throw IllegalInputData("each job must have > 1 task");
    }

    // 生成任务
    the_job = new job(i);  // 给任务编号
    cout << "Enter the tasks (machine , time)"
         << " in process order" << endl;  // 有序输入任务的工序

    for (int j = 1; j <= num_tasks; j++) {  // 把工序放入任务中
      cin >> the_machine >> the_task_time;
      if (the_machine < 1 || the_machine > num_machines || the_task_time < 1)
        throw IllegalInputData("bad machine number or task time");
      if (j == 1) first_machine = the_machine;  // 该任务的第一道工序的机器
      the_job->addTask(the_machine, the_task_time);  // 把工序加到任务里面
    }

    m_array[first_machine].jobQ.push(the_job);  // 移入机器队列
  }
};

// 改变某台机器的运行状态
job* changeState(int the_machine) {
  job* lastJob;  // 上一个任务
  if (m_array[the_machine].activeJob ==
      NULL) {        // 如果机器目前处于空闲或者转换状态
    lastJob = NULL;  // 等待新任务
    if (m_array[the_machine].jobQ.empty()) {
      // 如果等待队列在没有任务，设为闲置
      e_list->setFinishTime(the_machine, largeTime);
    } else {  // 若本机器的任务队列里面还有任务
      m_array[the_machine].activeJob = m_array[the_machine].jobQ.front();
      // 从队列中提取下一个任务，在机器上执行
      m_array[the_machine].jobQ.pop();
      m_array[the_machine].totalWait +=
          (time_now - m_array[the_machine].activeJob->arrivalTime);
      m_array[the_machine].numTasks++;
      // 完成本任务的对应工序所需时间为t（当进入机器运作的时候，task队列就把改tasl删除了）
      int t = m_array[the_machine].activeJob->removeNextTask();
      e_list->setFinishTime(the_machine, time_now + t);  // 设置完成时间
    }
  } else {  // 机器上有任务，那么完成该任务，进入转换状态
    lastJob = m_array[the_machine].activeJob;
    m_array[the_machine].activeJob = NULL;  // 进入转换状态
    // 设置转换状态的结束时间
    e_list->setFinishTime(the_machine,
                          time_now + m_array[the_machine].changeTime);
  }
  return lastJob;  // 返回进行完的任务
};

// 启动仿真过程
void startShop() {
  // 在每台机器上装载第一个任务
  for (int p = 1; p <= num_machines; p++) {
    changeState(p);  // 在每台机器上状态第一个任务
  }
};

// 任务中某工序完成，转移到另外一台机器的任务队列上
bool moveToNextMachine(job* the_job) {
  // 如果任务已完成，则返回false

  if (the_job->taskQ.empty()) {  // 没有下一道工序
    cout << "Job " << the_job->id << " has completed at " << time_now
         << " Total wait was" << (time_now - the_job->length) << endl;
    return false;
  } else {
    // 任务the_job有下一道工序
    // 确定执行下一道工序的机器
    int p = the_job->taskQ.front().machine;
    m_array[p].jobQ.push(the_job);
    the_job->arrivalTime = time_now;
    // 如果机器p空闲，则改变它的状态
    if (e_list->nextEventTime(p) == largeTime) {
      changeState(p);
    }
    return true;
  }
};

// 处理所有未处理的任务
void simulate() {
  while (num_jobs > 0) {  // 至少有一个任务未处理
    // 获得下一个要处理的任务所在的机器号
    int nextToFinish = e_list->nextEvenMachine();
    // 完成这个任务对应的工序 ，到达任务在机器上调度结束的时间
    time_now = e_list->nextEventTime(nextToFinish);
    // 改变机器上nextToFinish任务
    job* the_job = changeState(nextToFinish);  // 状态转换，接收该机器完成的任务
    // 把任务the_job放到下一个调度机器上面去
    // 如果the_job任务完成则减少任务数
    if (the_job != NULL && !moveToNextMachine(the_job)) {
      num_jobs--;
    }
  }
};

// 输出所有任务完成的最后时间，和每台机器的统计信息
void outputStatistics() {
  // 输出每台机器上的等待时间
  cout << "Finish time = " << time_now << endl;
  for (int p = 1; p <= num_machines; p++) {
    cout << "Machine " << p << "completed " << m_array[p].numTasks << " tasks"
         << endl;
    cout << "Total wait time was " << m_array[p].totalWait << endl;
    cout << endl;
  }
};

int main() {
  inputData();         // get machine and job data
  startShop();         // initial machine loading
  simulate();          // run all jobs through shop
  outputStatistics();  // output machine wait times
};

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
