#pragma once
#include <iostream>

#include "arrayStack.h"
#include "myExceptions.h"

// ��n��Ԫ�ش���x���ƶ�����y�н�����z,������ջ
void towerOfHanoiWithRescursion(int n, int x, int y, int z) {
  if (n > 0) {
    towerOfHanoiWithRescursion(n - 1, x, z, y);  // ��n-1������x�ƶ���z����y
    std::cout << "Move top disk " << n << " ) from tower " << x << " to tower "
              << y << std::endl;  // �ѵ�ǰn�����ĵ���x�ŵ�y
    towerOfHanoiWithRescursion(n - 1, z, y,
                               x);  // ����ת���ɽ�z�е�n-1������ת��y�н���x
  }
};  // �����ֻ��ʾ�ƶ�����������ʽÿ��ʱ����һ�����Ĳ���

arrayStack<int> tower[4];  // �����洢���Ĳ���

// �ݹ麯��
void moveAndShow(int n, int x, int y, int z) {
  if (n > 0) {
    moveAndShow(n - 1, x, z, y);
    int d = tower[x].top();  // ��ջ�����һ��Ԫ��
    tower[x].pop();          // ��x��ջ
    tower[y].push(d);        // ��ջy
    std::cout << "Move disk " << d << " from tower " << x << " to top of tower "
              << y << std::endl;
    moveAndShow(n - 1, z, y, x);
  }
}

// ��ջ����ʾ
void towerOfHanoiWithStack(int n, int x, int y, int z) {
  // Ԥ����
  for (int d = n; d > 0; d--) {
    tower[1].push(d);  // �Ӵ�С������ջ
  }
  moveAndShow(n, 1, 2, 3);
};