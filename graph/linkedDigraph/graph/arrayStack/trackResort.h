#pragma once
#include <iostream>
#include "arrayStack.h"
#include "myExceptions.h"

arrayStack<int> *track;  // ����������
int numberOfCars;        // ��ǰ������
int numberOfTracks;      // ��ǰ�����
int smallestCar;         // �ڻ������б����С�ĳ���
int itsTrack;            // ͣ������С��ų���Ļ�����

// �������С�ĳ���ӻ������Ƶ������
void outputFromHoldingTrack() {
  // ��ջitsTrack��ɾ�������С�ĳ���
  track[itsTrack].pop();
  std::cout << "Move car " << smallestCar << " from holding "
            << "track " << itsTrack << " to output track" << std::endl;

  // ������е�ջ��ջ����Ѱ�ұ����С�ĳ�����������Ļ�����:ջitsTrack
  // ����smallestCar�Ѿ��Ƴ���������С�ĳ��ᣬ���������û�г�����ô��ΪnumberOfCars+2
  smallestCar = numberOfCars + 2;
  // ����Ϊʲô����ΪnumberOfCars+2������numberOfCars+1�أ���
  // ��ΪsmallestCar=numberOfCar+1������Ϊ�˻������޳���ı�ʶ
  for (int i = 1; i < numberOfTracks; i++) {
    if (!track[i].empty() && (track[i].top() < smallestCar)) {
      smallestCar = track[i].top();
      itsTrack = i;
    }
  }
};

// ������c�ƶ���һ��������������false���ҽ�����ǰû�п��õĻ�����
bool putInHoldingTrack(int c) {
  // Ϊ����cѰ������ʵĻ�����
  // ��ʼ��
  int bestTrack = 0;               // Ŀǰ��õĳ��ᣬ��ʼ��Ϊ0
  int bestTop = numberOfCars + 1;  // ȡBesttrack�����ĳ���

  // ɨ�軺����
  for (int i = 1; i <= numberOfTracks; i++) {
    if (!track[i].empty()) {        // i�������
      int topCar = track[i].top();  // ȡ�����������ĳ���
      if (c < topCar &&
          topCar < bestTop) {  // ������i��ջ�����б�Ÿ�С�ĳ��ᣨ����ʵĹ����
        bestTop = topCar;      // ��������õĳ������Ϊ��ó���
        bestTrack = i;         // ��ù������Ϊ������
      }
    } else {  // ���������iΪ��
      if (bestTrack == 0) {  // ����û�и����ʵĹ�����ѿչ������Ϊ��ѹ��
        bestTrack = i;  // ��Ϊ��ѹ��
      }
    }
  }

  if (bestTrack == 0) return false;  // ���û�п��ó��ᣬ����false

  // ���뻺����
  track[bestTrack].push(c);
  std::cout << "Move car " << c << " from input track "
            << "to holding track " << bestTrack << std::endl;

  // �����Ҫ������smallestTrack��itsTrack
  if (c < smallestCar) {
    smallestCar = c;
    itsTrack = bestTrack;
  }
  return true;
};

bool railroad(int inputOrder[], int the_numberOfCars, int the_numberOfTracks) {
  // �ӳ�ʼ˳��ʼ����
  // ������гɹ�����true���򷵻�false

  numberOfCars = the_numberOfCars;
  numberOfTracks = the_numberOfTracks;

  // �������ڻ�������ջ
  track = new arrayStack<int>[numberOfTracks + 1];  // ����Ϊ0�Ŀ���

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