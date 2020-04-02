#pragma once
#include <iostream>

#include "hash.h"
#include "myExceptions.h"

template <typename K, typename E>
class hashTable {
 protected:
  int search(const K&) const;     // 寻找键值为key的数对
  std::pair<const K, E>** table;  // hash表
  myHash::hash<K> hash;           // 把类型K映射成一个非负整数
  int dSize;                      // 字典中的数对
  int divisor;                    // 散列函数的除数
 public:
  hashTable(int theDivisor = 11);
  ~hashTable() { delete[] table; };

  bool empty() { return dSize == 0; };
  int size() const { return dSize; };
  std::pair<const K, E>* find(const K& theKey) const;
  void insert(const std::pair<const K, E>&);
  void output(std::ostream& out) const;
};

template <typename K, typename E>
hashTable<K, E>::hashTable(int theDivisor) {
  divisor = theDivisor;
  dSize = 0;

  // 分配空间并初始化
  table = new std::pair<const K, E>*[divisor];
  for (int i = 0; i < divisor; i++) table[i] = NULL;
};

// 线性探查（找到下一个可用桶）
template <typename K, typename E>
int hashTable<K, E>::search(const K& theKey) const {
  // 搜索一个公开地址散列表，查找关键字为theKey的数对
  // 如果匹配的数对还存在，返回他的位置，否则，如果散列表不满，
  // 返回关键字为theKey的数对可以插入的位置

  int i =
      (int)hash(theKey) % divisor;  // 将他和 Key转化为非负整数再用在散列函数上
  int j = i;
  do {
    // 找到了theKey匹配的数对或者找到了可以插入的位置
    if (table[j] == NULL || table[j]->first == theKey) return j;
    j = (j + 1) % divisor;  // 一次搜索散列表，知道回到f(theKey)的位置
  } while (j != i);

  return j;  // 返回起始桶
};

template <typename K, typename E>
std::pair<const K, E>* hashTable<K, E>::find(const K& theKey) const {
  // 返回匹配数对的指针
  // 如果数对不存在则返回NULL

  // 搜索散列表
  int b = search(theKey);

  // 判断table[b]是否是匹配数对
  if (table[b] == NULL || table[b]->first != theKey) return NULL;  // 没找到

  return table[b];  // 返回匹配数对
};

template <typename K, typename E>
void hashTable<K, E>::insert(const std::pair<const K, E>& thePair) {
  // 把数对插入到字典里，若存在相同关键字的数对则覆盖
  // 若表满，抛出异常

  // 搜索散列表
  int b = search(thePair.first);

  // 检查匹配数对是否存在
  if (table[b] == NULL) {
    table[b] = new std::pair<const K, E>(thePair);  // 创建新桶
    dSize++;
  }

  else {
    // 检查是有关键字一样的数对
    if (table[b]->first == thePair.first)
      table[b]->second = thePair.second;  // 有则覆盖

    else  // 表满
      std::cout << " Table is full already! "
                << "\ninsert fail!" << std::endl;
  }
};

template <typename K, typename E>
void hashTable<K, E>::output(std::ostream& out) const {
  for (int i = 0; i < divisor; i++) {  // 查找所有桶
    if (table[i] == NULL)              // 空桶输出NULL
      std::cout << "NULL" << std::endl;
    else
      std::cout << "<" << table[i]->first << " " << table[i]->second << ">\n";
  }
};

template <typename K, typename E>
std::ostream& operator<<(std::ostream& out, const hashTable<K, E>& x) {
  x.output(out);
  return out;
};
