#pragma once
#include <iostream>

#include "dictionary.h"
#include "hash.h"
#include "sortedChain.h"

template <typename K, typename E>
class hashChains : public dictionary<K, E> {
 public:
  hashChains(int theDivisor = 11) {
    divisor = theDivisor;
    dSize = 0;

    // 分配内存空间
    table = new sortedChain<K, E>[divisor];
  };

  ~hashChains() { delete[] table; };

  bool empty() const { return dSize == 0; };
  int size() const { return dSize; };

  std::pair<const K, E>* find(const K& theKey) const {
    // 用散列函数找到对应的桶，在桶上找Key
    return table[hash(theKey) % divisor].find(theKey);
  };
  // 插入数对
  void insert(const std::pair<const K, E>& thePair) {
    int homeBucket = (int)hash(thePair.first) % divisor;  // 找到起始桶
    int homeSize =
        table[homeBucket].size();  // 找到该桶里面有多少数对(插入之前的长度)
    table[homeBucket].insert(thePair);
    if (table[homeBucket].size() > homeSize)  // 插入成功
      dSize++;                                // 更新数对的数量
  };

  // 删除数对
  void erase(const K& theKey) { table[hash(theKey) % divisor].erase(theKey); };

  void output(std::ostream& out) const {
    for (int i = 0; i < divisor; i++) {
      if (table[i].size() == 0)  // 如果该桶没有元素
        std::cout << "NULL" << std::endl;
      else
        std::cout << table[i] << std::endl;
    }
  }

 protected:
  sortedChain<K, E>* table;  // 散列链表
  myHash::hash<K> hash;      // 映射函数
  int dSize;                 //  数对数量
  int divisor;               // 桶数即散列表长度
};

template <typename K, typename E>
std::ostream& operator<<(std::ostream& out, const hashChains<K, E>& x) {
  x.output(out);
  return out;
};