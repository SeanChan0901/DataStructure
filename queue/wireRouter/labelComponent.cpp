#include "labelComponents.h"
#include "position.h"
using namespace std;

// ����ͼ��
void inputImage() {  // Input the image.
  cout << "Enter image size" << endl;
  cin >> picture_size;

  // create and input the pixel array
  make2dArray(pixel, picture_size + 2, picture_size + 2);
  cout << "Enter the pixel array in row-major order" << endl;
  for (int i = 1; i <= picture_size; i++)
    for (int j = 1; j <= picture_size; j++) cin >> pixel[i][j];
};

// ���ͼ��
void outputImage() {  // Output labeled image.

  cout << "The labeled image is" << endl;
  for (int i = 1; i <= picture_size; i++) {
    for (int j = 1; j <= picture_size; j++) cout << pixel[i][j] << "  ";
    cout << endl;
  }
};

  // ��ͼԪ���
void labelComponents() {
  // ��ʼ��ƫ����
  // ��ʼ������offset
  position offset[4];
  offset[0].row = 0;
  offset[0].col = 1;
  offset[1].row = 1;
  offset[1].row = 0;
  offset[2].row = 0;
  offset[2].col = -1;
  offset[3].row = -1;
  offset[3].col = 0;

  // ��ʼ��0ֵ����Χǽ
  for (int i = 0; i <= picture_size + 1; i++) {
    pixel[0][i] = pixel[0][picture_size + 1] = 0;  // �ײ��Ͷ���
    pixel[i][0] = pixel[i][picture_size + 1] = 0;  // �����
  }

  int numOfNbrs = 4;  // һ�����ص�����λ����

  // ɨ���������� ���ͼԪ
  arrayQueue<position> q;
  position here, nbr;
  int id = 1;                                  // ͼԪid
  for (int r = 1; r <= picture_size; r++) {    // ͼ�����r
    for (int c = 1; c <= picture_size; c++) {  // ͼ�����c
      if (pixel[r][c] == 1) {
        // ��ͼԪ
        pixel[r][c] = ++id;  // ȡ��һ��id
        here.row = r;
        here.col = c;

        while (true) {
          // Ѱ�������ͼԪ,֪��ͬһ��ͼԪ������ȫ��������
          for (int i = 0; i < numOfNbrs; i++) {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (pixel[nbr.row][nbr.col] == 1) {
              // �����ǵ�ǰͼԪ��һ����
              pixel[nbr.row][nbr.col] = id;
              q.push(nbr);
            }
          }

          // �����ܱߵ�ͼԪ����z֮�󣬿���ͼԪ������δ���������
          if (q.empty()) {
            break;
          }
          here = q.front();
          q.pop();
        }
      }
    }
  }
};