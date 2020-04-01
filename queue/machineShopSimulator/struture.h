#pragma once
#include "arrayQueue.h"
#include "myExceptions.h"
// ������Ϊһ�����ݽṹ
struct task {
  int machine;  // �ù���ռ�õĻ���
  int time;     // ��ɸù�����Ҫ��ʱ
  task(int the_machine = 0, int the_time = 0) {
    machine = the_machine;
    time = the_time;
  }
};

// ������Ϊһ�����ݽṹ��ÿ�����������ɸ�����
struct job {
  arrayQueue<task> taskQ;  // ��������
  int length;              // �����ȵĹ����ʱ���ܺ�
  int arrivalTime;         // ���ﵱǰ�������е�ʱ��
  int id;                  // ������
  job(int the_Id = 0) {
    id = the_Id;
    length = 0;
    arrivalTime = 0;
  };

  void addTask(int the_machine, int the_time) {
    task the_task(the_machine, the_time);
    taskQ.push(the_task);
  };

  int removeNextTask() {  // ɾ���������һ�����򣬷�������Ҫ��ʱ��
    int the_time = taskQ.front().time;
    taskQ.pop();
    length += the_time;
    return the_time;
  }
};

// �����ṹ
struct machine {
  arrayQueue<job*> jobQ;  // �����ϵȴ�����
  // ����ÿ���������κ�ʱ��ֻ����һ���������������Զ��г���Ӧ����������ĿΪ��
  int changeTime;  // ��������ת��ʱ��
  int totalWait;   // ��������������ʱ
  int numTasks;    // ����������Ĺ�������
  job* activeJob;  // ��������ǰ���������

  machine() {
    totalWait = 0;
    numTasks = 0;
    activeJob = NULL;
  }
};

// ���л��������ʱ�䱻����Ϊ�ܴ��һ����
class eventList {
 public:
  eventList(int the_num_machines, int the_large_time);
  int nextEvenMachine();  // Ҫ������һ���¼��ĵĻ���

  // ���ؽ�Ҫ������һ�¼���ʱ�䣨���Ƿ��ػ����Ľ���ʱ�䣩
  int nextEventTime(int theMachine) { return finishTime[theMachine]; };

  // ���ý���ʱ��
  void setFinishTime(int the_machine, int the_time) {
    finishTime[the_machine] = the_time;
  }
  ~eventList();

 private:
  int* finishTime;  // ���ʱ������
  int numMachines;   // ��������
};

eventList::eventList(int the_num_machine, int the_large_time) {
  // Ϊm̨��������ʼ�������ʱ��
  if (the_num_machine < 1) {
    throw IllegalParameterValue("number of machine nust be >= 1");
  }
  numMachines = the_num_machine;          // ���»�������
  finishTime = new int[numMachines + 1];  // m̨���������ʱ��

  // ���л��������У��ô�����ʱ���ʼ��
  for (int i = 1; i <= numMachines; i++) {
    finishTime[i] = the_large_time;
  }
};

  // Ҫ������һ���¼��ĵĻ���
int eventList::nextEvenMachine() {
  // ����ֵ�Ǵ�����һ���Ļ���

  // Ѱ�����ʱ������Ļ���,������ɹ���Ļ���������һ���¼�
  int p = 1;
  int t = finishTime[1];
  for (int i = 2; i <= numMachines; i++) {  // �����л������ҽ���ʱ��
    if (finishTime[i] < t) {                // ����i���ʱ�����
      p = i;
      t = finishTime[i];
    }
  }
  return p;
};





eventList::~eventList() {}