
#include <fstream>
#include <iostream>

#include "hashChains.h"

using namespace std;

// 常量
const int DIVISOR = 4099;    // 散列函数的除数
const int MAX_CODES = 4096;  // 字典的最大容量
const int BYTE_SIZE = 8;     // 一个字节8位
const int EXCESS =
    4;  // 由于每个压缩后的代码是12位数，不能一个字节输出，余下4位
const int ALPHA =
    256;  // 一个字节能表示的最大字符数量位256（2^8）
const int MASK1 = 255;  // ALPHA - 1 二进制为11111111
const int MASK2 = 15;   // 2^EXCESS - 1  二进制为1111

// 数对
typedef pair<const long, int> pairType;

// 全局变量
int leftOver;               // 记录代码剩下未输出的四位
bool bitsLeftOver = false;  // 代码有余位待输出
std::ifstream in;           // 从文件读入
std::ofstream out;          // 输出到文件

// 建立输入输出流：打开输入和输出文件
void setFiles(int argc, char* argv[]) {
  // 建立输入输出流
  char outputFile[50], inputFile[54];
  // 检查是否有文件名
  if (argc >= 2) {
    strcpy(inputFile, argv[1]);  // 记录文件名到inputFile中（长度不超过50）
  } else {  // 没有输入文件名，则输入文件名
    cout << "Enter name of file to compress" << endl;
    cin >> inputFile;
  }

  // 打开二进制文件
  in.open(inputFile, ios::binary);
  if (in.fail()) {
    cerr << "Can not open " << inputFile << endl;
    exit(1);
  }
  strcpy(outputFile, inputFile);  // 复制文件名
  strcat(outputFile, ".comp");    // 输出文件名改成outputFile.zzz
  cout << outputFile << endl;
  out.open(outputFile, ios::binary);  // 打开这个文件
};

// 代码输出
void output(long pcode) {
  // 输出8位，把剩余的位保存
  int c, d;
  // 有余位待输出
  if (bitsLeftOver) {
    d = int(pcode & MASK1);  // 保存后8位
    c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
    out.put(
        c);  // 左四位与上一个字节的8位组合成了一个12位（代码），右四位就是下一个代码的前四位
    out.put(d);            // 下一个代码的后8位
    bitsLeftOver = false;  // 没有余位了
  } else {
    leftOver = pcode & MASK2;  // 保留右四位
    c = int(pcode >> EXCESS);
    out.put(c);
    bitsLeftOver = true;  // 有余位待输出
  }
};

// LZW压缩
void compress() {
  // LZW压缩器
  // 定义和初始化代码字典
  // 代码12位长，关键字20位长
  hashChains<long, int> h(DIVISOR);
  // 将256个字符全部放入字典
  for (int i = 0; i < ALPHA; i++) h.insert(pairType(i, i));
  int codesUsed = ALPHA;  // 代码共有ALPAH个

  // 输入和压缩
  int c = in.get();  // 输入文件的第一个字符
  if (c != EOF) {    // 文件不空
    long pcode = c;  // 前缀代码
    while ((c = in.get()) != EOF) {
      // 处理字符c
      long theKey = (pcode << BYTE_SIZE) + c;  // pc
      // 查看pc是否在字典中
      pairType* thePair = h.find(theKey);
      if (thePair == NULL) {  // 新的最长字串p
        // 关键字不在表中
        output(pcode);              // 输出这个p的代码
        if (codesUsed < MAX_CODES)  // 字典未满
          h.insert(pairType((pcode << BYTE_SIZE) | c,
                            codesUsed++));  // 把代码存入字典
        pcode = c;
      } else
        pcode =
            thePair
                ->second;  // 关键字theKey在表中,先不输出代码，找最长匹配字符串
    }
    output(pcode);  // 输出该代码（前缀）
    if (bitsLeftOver) out.put(leftOver << EXCESS);  // 保证12位输出
  }
  out.close();
  in.close();
};

int main(int argc, char* argv[]) {
  setFiles(argc, argv);
  compress();
  return 0;
};