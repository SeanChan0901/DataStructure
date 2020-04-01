#pragma once
#include <iostream>
#include "arrayQueue.h"
#include "myExceptions.h"

arrayQueue<int> *track;  // ����������
int numberOfCars;        // ��ǰ������
int numberOfTracks;      // ��ǰ�����
int smallestCar;         // �ڻ������б����С�ĳ���
int itsTrack;            // ͣ������С��ų���Ļ�����

// �������С�ĳ���ӻ������Ƶ������
void outputFromHoldingTrack() {
  // �������С�ĳ���ӻ��������Ƴ��������
  track[itsTrack].pop();
  std::cout << "Move car " << smallestCar << " from holding track" << itsTrack
            << " to output track" << std::endl;

  // ������ж��еĶ���ͷ��Ѱ�ұ����С�ĳ�����������Ļ�����
  smallestCar = numberOfCars + 2;
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty() && track[i].front() < smallestCar) {
      smallestCar = track[i].front();  // �ҵ���С�ĳ���
      itsTrack = i;                    // ���¹��
    }
  }
};

// ������c�ƶ���һ��������������false���ҽ�����ǰû�п��õĻ�����
bool putInHoldingTrack(int c) {
  // Ϊ����cѰ������ʵĻ�����
  // ��ʼ��
  int bestTrack = 0;  // Ŀǰ����ʵĹ��
  int bestLast = 0;  // ȡbestTrack�����ĳ��ᣨ��

  // ɨ�軺����
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty()) {  // ����ǿ�
      int lastCar = track[i].back();  // ȡ��β��Ԫ��
      if (c>lastCar&&lastCar>bestLast) {
        bestLast = lastCar;  // �������Ŷ�β
        bestTrack = i;  // �������Ź��
      }
    } else {  // ���iΪ��
      if (bestTrack==0) {  // ���û�и��õĻ�������
        bestTrack = i;
      }
    }
  }

  // Ѱ�����Ź������
  if (bestTrack==0) {  // �������û���ҵ����Ź��
    return false;  // ʧ��
  }

  track[bestTrack].push(c);  // ���뻺����
  std::cout << "Move car " << c << "from input track "
            << "to holding track" << bestTrack << std::endl;

  if (c<smallestCar) {  // �������С�ĳ��ᣬ��Ҫ���������Ϣ
    smallestCar = c;
    itsTrack = bestTrack;
  }
  return true;
};

bool railroad(int inputOrder[], int the_numberOfCars, int the_numberOfTracks) {
  // �ӳ�ʼ˳��ʼ����
  // ������гɹ�����true���򷵻�false

  numberOfCars = the_numberOfCars;
  numberOfTracks = the_numberOfTracks-1;  // ��k������������ֱ�����

  // �������ڻ�������ջ
  track = new arrayQueue<int>[numberOfTracks + 1];  // ����Ϊ0�Ŀ���

  int nextCarToOutput = 1;         // ��һ����Ҫ����ĳ��ᣬ��Ϊ1
  smallestCar = numberOfCars + 1;  // ���������޳���

  // ���ų���
  for (int i = 1; i <= numberOfCars; i++) {
    if (inputOrder[i] ==
        nextCarToOutput) {  // ��������������һ��Ҫ���Ƴ��ĳ���
      std::cout << "Move car " << inputOrder[i]
                << " from input track to output track" << std::endl;
      nextCarToOutput++;  // ������һ��Ҫ����ĳ���

      // �ӻ������Ƶ������
      while (smallestCar == nextCarToOutput) {
        outputFromHoldingTrack();
        nextCarToOutput++;
      }
    } else {  // ���������᲻��Ҫ����ĳ���ͽ������뻺����
      if (!putInHoldingTrack(inputOrder[i])) {
        return false;  // �޷����뻺��������ô����ʧ��
      }
    }
  }
  return true;  // ���ųɹ�
};