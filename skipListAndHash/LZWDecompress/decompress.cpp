#include <fstream>
#include <iostream>

using namespace std;

// 常量
const int MAX_CODES = 4096;  // 最大代码数
const int BYTE_SIZE = 8;     // 字节位数
const int EXCESS = 4;        //
const int ALPHA = 256;       // 初始表
const int MASK = 15;         // 后四位

typedef pair<int, char> pairType;

// 全局变量
pairType ht[MAX_CODES];     // 字典
char s[MAX_CODES];          // 用来重建文本
int CodeSize;               //重建文本的大小
int leftOver;               // 待输出代码位
bool bitsLeftOver = false;  // false表示没有余位置
ifstream in;
ofstream out;

// 建立输入输出流：打开输入和输出文件
void setFiles(int argc, char* argv[]) {
  // 建立输入输出流
  char outputFile[50], inputFile[54];
  // see if file name provided
  if (argc == 2)
    strcpy(outputFile, argv[1]);
  else {  // 文件名未输入，输入文件名
    cout << "Enter name of file to decompress" << endl;
    cout << "Omit the extension .dec" << endl;
    cin >> outputFile;
  }

  strcpy(inputFile, outputFile);
  strcat(inputFile, ".comp");

  // o打开二进制文件
  in.open(inputFile, ios::binary);
  if (in.fail()) {
    cerr << "Cannot open " << inputFile << endl;
    exit(1);
  }
  out.open(outputFile, ios::binary);
};

// 计算text
void output(int code) {  // 在字典中找code
  // 输出与代码code对应的串
  CodeSize = (-1);
  while (code >= ALPHA) {
    // 意思就是不是单个字符了，是组合字符，代表后缀
    s[++CodeSize] = ht[code].second;  // 把后缀存储下来
    code = ht[code].first;            // 找他的前缀，继续解析前缀
  }
  s[++CodeSize] = code;  // 直到code解析到单个字符为止
  for (int i = CodeSize; i >= 0; i--) {
    out.put(i);  // 由于是从右到左存储后缀，输出的时候要反向
  }
};

// 获取12位代码
bool getCode(int& code) {
  // 把压缩文件中的下一个代码存入code
  // 如果不再有代码返回false
  int c, d;
  if ((c = in.get()) == EOF) return false;  // 读完了，返回false

  // 检查前面是否有剩余的为
  // 如果有，与其连接
  if (bitsLeftOver) {
    code = ((leftOver << BYTE_SIZE) | c);  // 跟余位拼成12位
  } else {
    d = in.get();  // 另外8位
    code =
        ((c << EXCESS) | (d >> EXCESS));  // c中的左8位和d中的右四位组成一个12位
    leftOver = d & MASK;                  // 存储4位
  }
  bitsLeftOver = !bitsLeftOver;
  return true;
};

// 解压缩
void decompress() {
  // 解压一个压缩文件
  int codesUsed = ALPHA;  // 当前代码量

  // 输入和解压缩
  int pcode;  // 前面的代码
  int ccode;  // 当前代码

  if (getCode(pcode)) {
    // 文件不空
    s[0] = pcode;   // 第一个代码肯定在字典存在（单个字符）
    out.put(s[0]);  // 输出该字符
    CodeSize = 0;   // s[CodeSize]是最后一个输出穿的第一个字符

    while (getCode(ccode)) {
      // 获取下一个代码
      if (ccode < codesUsed)  // 在字典里面
      {                       // 确定ccode
        output(
            ccode);  // 转化为字符串，ccode变成了后缀（即下一个字符串的第一个字符）
        if (codesUsed < MAX_CODES) {
          // 建立新代码
          ht[codesUsed].first = pcode;           // 前面的代码（前缀）
          ht[codesUsed++].second = s[CodeSize];  // 后缀
        }
      } else {
        // 特殊情况，字典中没有ccode 即ccode>codesUsed
        ht[codesUsed].first = pcode;
        ht[codesUsed++].second = s[CodeSize];  // 先定义ccode到字典里
        output(ccode);                         // 再解它
      }
    }
  }

  out.close();
  in.close();
}

int main(int argc, char* argv[]) {
  setFiles(argc, argv);
  decompress();
  return 0;
}