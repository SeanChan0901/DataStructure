#include "labelComponents.h"
#include "position.h"
using namespace std;

// 输入图像
void inputImage() {  // Input the image.
  cout << "Enter image size" << endl;
  cin >> picture_size;

  // create and input the pixel array
  make2dArray(pixel, picture_size + 2, picture_size + 2);
  cout << "Enter the pixel array in row-major order" << endl;
  for (int i = 1; i <= picture_size; i++)
    for (int j = 1; j <= picture_size; j++) cin >> pixel[i][j];
};

// 输出图像
void outputImage() {  // Output labeled image.

  cout << "The labeled image is" << endl;
  for (int i = 1; i <= picture_size; i++) {
    for (int j = 1; j <= picture_size; j++) cout << pixel[i][j] << "  ";
    cout << endl;
  }
};

  // 给图元编号
void labelComponents() {
  // 初始化偏移量
  // 初始化数组offset
  position offset[4];
  offset[0].row = 0;
  offset[0].col = 1;
  offset[1].row = 1;
  offset[1].row = 0;
  offset[2].row = 0;
  offset[2].col = -1;
  offset[3].row = -1;
  offset[3].col = 0;

  // 初始化0值像素围墙
  for (int i = 0; i <= picture_size + 1; i++) {
    pixel[0][i] = pixel[0][picture_size + 1] = 0;  // 底部和顶部
    pixel[i][0] = pixel[i][picture_size + 1] = 0;  // 左和右
  }

  int numOfNbrs = 4;  // 一个像素的相邻位置数

  // 扫描所有像素 标记图元
  arrayQueue<position> q;
  position here, nbr;
  int id = 1;                                  // 图元id
  for (int r = 1; r <= picture_size; r++) {    // 图像的行r
    for (int c = 1; c <= picture_size; c++) {  // 图像的列c
      if (pixel[r][c] == 1) {
        // 新图元
        pixel[r][c] = ++id;  // 取下一个id
        here.row = r;
        here.col = c;

        while (true) {
          // 寻找其余的图元,知道同一个图元的像素全部被找齐
          for (int i = 0; i < numOfNbrs; i++) {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (pixel[nbr.row][nbr.col] == 1) {
              // 像素是当前图元的一部分
              pixel[nbr.row][nbr.col] = id;
              q.push(nbr);
            }
          }

          // 找完周边的图元像素z之后，考察图元中任意未考察的像素
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