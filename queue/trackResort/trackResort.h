#pragma once
#include <iostream>
#include "arrayQueue.h"
#include "myExceptions.h"

arrayQueue<int> *track;  // 缓冲轨道组数
int numberOfCars;        // 当前车厢数
int numberOfTracks;      // 当前轨道数
int smallestCar;         // 在缓冲轨道中编号最小的车厢
int itsTrack;            // 停靠着最小编号车厢的缓冲轨道

// 将编号最小的车厢从缓冲轨道移到出轨道
void outputFromHoldingTrack() {
  // 将编号最小的车厢从缓冲轨道中移出到出轨道
  track[itsTrack].pop();
  std::cout << "Move car " << smallestCar << " from holding track" << itsTrack
            << " to output track" << std::endl;

  // 检查所有队列的队列头，寻找编号最小的车厢和他所属的缓冲轨道
  smallestCar = numberOfCars + 2;
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty() && track[i].front() < smallestCar) {
      smallestCar = track[i].front();  // 找到最小的车厢
      itsTrack = i;                    // 更新轨道
    }
  }
};

// 将车厢c移动到一个缓冲轨道。返回false当且仅当当前没有可用的缓冲轨道
bool putInHoldingTrack(int c) {
  // 为车厢c寻找最合适的缓冲轨道
  // 初始化
  int bestTrack = 0;  // 目前最合适的轨道
  int bestLast = 0;  // 取bestTrack中最后的车厢（）

  // 扫描缓冲轨道
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty()) {  // 轨道非空
      int lastCar = track[i].back();  // 取队尾的元素
      if (c>lastCar&&lastCar>bestLast) {
        bestLast = lastCar;  // 更新最优队尾
        bestTrack = i;  // 更新最优轨道
      }
    } else {  // 轨道i为空
      if (bestTrack==0) {  // 如果没有更好的缓冲轨道了
        bestTrack = i;
      }
    }
  }

  // 寻找最优轨道结束
  if (bestTrack==0) {  // 如果还是没有找到最优轨道
    return false;  // 失败
  }

  track[bestTrack].push(c);  // 放入缓冲轨道
  std::cout << "Move car " << c << "from input track "
            << "to holding track" << bestTrack << std::endl;

  if (c<smallestCar) {  // 如果是最小的车厢，还要更新相关信息
    smallestCar = c;
    itsTrack = bestTrack;
  }
  return true;
};

bool railroad(int inputOrder[], int the_numberOfCars, int the_numberOfTracks) {
  // 从初始顺序开始排列
  // 如果排列成功返回true否则返回false

  numberOfCars = the_numberOfCars;
  numberOfTracks = the_numberOfTracks-1;  // 第k条缓冲轨道用于直接输出

  // 创建用于缓冲轨道的栈
  track = new arrayQueue<int>[numberOfTracks + 1];  // 索引为0的空置

  int nextCarToOutput = 1;         // 下一个需要输出的车厢，设为1
  smallestCar = numberOfCars + 1;  // 缓冲轨道中无车厢

  // 重排车厢
  for (int i = 1; i <= numberOfCars; i++) {
    if (inputOrder[i] ==
        nextCarToOutput) {  // 如果这个车厢是下一个要被移出的车厢
      std::cout << "Move car " << inputOrder[i]
                << " from input track to output track" << std::endl;
      nextCarToOutput++;  // 更新下一个要输出的车厢

      // 从缓冲轨道移到出轨道
      while (smallestCar == nextCarToOutput) {
        outputFromHoldingTrack();
        nextCarToOutput++;
      }
    } else {  // 如果这个车厢不是要输出的车厢就将他放入缓冲轨道
      if (!putInHoldingTrack(inputOrder[i])) {
        return false;  // 无法放入缓冲轨道，那么重排失败
      }
    }
  }
  return true;  // 重排成功
};