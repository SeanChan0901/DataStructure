#pragma once
#include <iostream>
#include "arrayStack.h"
#include "myExceptions.h"

arrayStack<int> *track;  // 缓冲轨道组数
int numberOfCars;        // 当前车厢数
int numberOfTracks;      // 当前轨道数
int smallestCar;         // 在缓冲轨道中编号最小的车厢
int itsTrack;            // 停靠着最小编号车厢的缓冲轨道

// 将编号最小的车厢从缓冲轨道移到出轨道
void outputFromHoldingTrack() {
  // 从栈itsTrack中删除编号最小的车厢
  track[itsTrack].pop();
  std::cout << "Move car " << smallestCar << " from holding "
            << "track " << itsTrack << " to output track" << std::endl;

  // 检查所有的栈的栈顶，寻找编号最小的车厢和他所属的缓冲轨道:栈itsTrack
  // 由于smallestCar已经移出，更新最小的车厢，如果缓冲轨道没有车厢那么设为numberOfCars+2
  smallestCar = numberOfCars + 2;
  // 这里为什么设置为numberOfCars+2而不是numberOfCars+1呢？？
  // 因为smallestCar=numberOfCar+1被设置为了缓冲轨道无车厢的标识
  for (int i = 1; i < numberOfTracks; i++) {
    if (!track[i].empty() && (track[i].top() < smallestCar)) {
      smallestCar = track[i].top();
      itsTrack = i;
    }
  }
};

// 将车厢c移动到一个缓冲轨道。返回false当且仅当当前没有可用的缓冲轨道
bool putInHoldingTrack(int c) {
  // 为车厢c寻找最合适的缓冲轨道
  // 初始化
  int bestTrack = 0;               // 目前最好的车厢，初始化为0
  int bestTop = numberOfCars + 1;  // 取Besttrack顶部的车箱

  // 扫描缓冲轨道
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty()) {        // i轨道不空
      int topCar = track[i].top();  // 取缓冲轨道顶部的车厢
      if (c < topCar &&
          topCar < bestTop) {  // 缓冲轨道i的栈顶具有编号更小的车厢（最合适的轨道）
        bestTop = topCar;      // 将这个更好的车厢更新为最好车厢
        bestTrack = i;         // 最好轨道更新为这个轨道
      }
    } else {  // 如果缓冲轨道i为空
      if (bestTrack == 0) {  // 而且没有更合适的轨道，把空轨道设置为最佳轨道
        bestTrack = i;  // 设为最佳轨道
      }
    }
  }

  if (bestTrack == 0) return false;  // 如果没有可用车厢，返回false

  // 放入缓冲轨道
  track[bestTrack].push(c);
  std::cout << "Move car " << c << " from input track "
            << "to holding track " << bestTrack << std::endl;

  // 如果需要，更新smallestTrack和itsTrack
  if (c < smallestCar) {
    smallestCar = c;
    itsTrack = bestTrack;
  }
  return true;
};

bool railroad(int inputOrder[], int the_numberOfCars, int the_numberOfTracks) {
  // 从初始顺序开始排列
  // 如果排列成功返回true否则返回false

  numberOfCars = the_numberOfCars;
  numberOfTracks = the_numberOfTracks;

  // 创建用于缓冲轨道的栈
  track = new arrayStack<int>[numberOfTracks + 1];  // 索引为0的空置

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