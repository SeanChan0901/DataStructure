#pragma once
#include <math.h>

#include <cmath>
#include <iostream>
#include <sstream>

#include "myExceptions.h"
#include "skipNode.h"

template <typename K, typename E>
class skipList {
 protected:
  float cutOff;                // 用来确定层数,相当于概率P
  int levels;                  // 当前最大非空链表
  int dSize;                   // 字典数对的个数
  int maxLevel;                // 允许的最大链表层数,从0开始
  K tailKey;                   // 最大关键字
  skipNode<K, E>* headerNode;  // 头节点指针
  skipNode<K, E>* tailNode;    // 尾节点指针
  skipNode<K, E>** last;       // last[i]表示i层最后的节点，i从0开始
 public:
  skipList(K large_key, int maxPairs = 10000, float probility = 0.5);
  ~skipList();
  std::pair<const K, E>* find(const K& the_key) const;
  int level() const;  // 级的分配函数
  // 搜索并把每一级链表搜索时所遇到的最后一个节点的指针存储起来
  skipNode<K, E>* search(const K& the_key) const;
  void insert(const std::pair<const K, E>& the_pair);
  void erase(const K& the_key);
  int size() const { return dSize; };
  void output(std::ostream& out) const;
};

// 构造函数
// 参数largeKey的值大于字典的任何数对的关键字，他存储在尾节点
// maxPairs是字典数对个数的最大值（通过maxlevel计算公式转化来的）
// 参数probability：是i-1级链表的数对同时也是i级链表的数对
template <typename K, typename E>
skipList<K, E>::skipList(K large_key, int maxPairs, float probability) {
  //关键值小于largeKey，且个数对数size最多为maxpairs。0<prob<1
  // 由于随机数生成器rand()产生的随机数大小是0～RANDMAX所以这里先乘以RAND_MAX方便处理
  cutOff = probability * RAND_MAX;
  // ceil向上取整，logf对数函数的用法
  maxLevel =
      (int)(std::ceil(std::logf((float)maxPairs) / logf(1 / probability)) - 1);
  levels = 0;
  dSize = 0;
  tailKey = large_key;

  // 生成头尾节点
  std::pair<K, E> tailPair;  // 尾部节点中的元素
  tailPair.first = tailKey;
  headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);  // 头节点
  tailNode = new skipNode<K, E>(tailPair, 0);               // 尾节点
  last = new skipNode<K, E>*[maxLevel + 1];  // 各层最后的节点

  // 链表为空的时候
  for (int i = 0; i <= maxLevel; i++) {
    headerNode->next[i] = tailNode;  // 各级链都指向尾节点
  }
};

template <typename K, typename E>
skipList<K, E>::~skipList() {
  // 删除所有节点
  skipNode<K, E>* nextNode;
  while (headerNode != tailNode) {
    nextNode = headerNode->next[0];
    delete headerNode;
    headerNode = nextNode;
  }
  delete tailNode;

  delete[] last;
};

// 如果关键字为the_key的数对不存在，返回NULL
// find从高级链表开始查找，直到0级链表
template <typename K, typename E>
std::pair<const K, E>* skipList<K, E>::find(const K& the_key) const {
  if (the_key >= tailKey) {
    std::cout << "the_key:" << the_key << "is too large" << std::endl;
    return NULL;  // 没有这样的数对
  }
  // 位置beforeNode是关键字为the_key的节点之前的最右边的位置
  skipNode<K, E>* beforeNode = headerNode;
  // 所有级的链，从高级到低级搜索
  for (int i = levels; i >= 0; i--) {
    // 一直找比the_key大的键值对（如果没有的话会一直找到尾节点，
    // 尾节点的element.first的key值为large_key一定是比the_key大的）
    while (beforeNode->next[i]->element.first < the_key)
      beforeNode = beforeNode->next[i];

    // 检查下一个节点的关键字是否是the_key
    if (beforeNode->next[0]->element.first == the_key)
      return &(beforeNode->next[0]->element);
  }
  // 没有找到关键字匹配的键值对
  return NULL;
};

template <typename K, typename E>
int skipList<K, E>::level() const {
  // 返回一个表示链表级数的随机数，随机数不大于maxLevel
  int lev = 0;
  while (std::rand() <= cutOff) lev++;
  return (lev <= maxLevel) ? lev : maxLevel;  // 不超过最大级
};

template <typename K, typename E>
skipNode<K, E>* skipList<K, E>::search(const K& the_key) const {
  // 搜索关键字the_key，把每一级链表中要查看的最后一个节点存储在数组last中（插入要用到）
  // 返回包含关键字the_key的节点
  // 位置beforedNode是关键字为the_key的节点的最右边的位置（当前级）
  skipNode<K, E>* beforeNode = headerNode;
  for (int i = levels; i >= 0; i--) {
    while (beforeNode->next[i]->element.first < the_key)
      beforeNode = beforeNode->next[i];
    last[i] = beforeNode;  // 把搜索遇到的每一级最后的节点存储起来
  }
  return beforeNode->next[0];
};

// 插入键值对到跳表中，如果key已经存在则更改他的value值
template <typename K, typename E>
void skipList<K, E>::insert(const std::pair<const K, E>& the_pair) {
  // 把数对the_pair插入字典，覆盖其关键字相同的已存在的数对
  if (the_pair.first >= tailKey) {
    std::ostringstream s;
    s << "Key = " << the_pair.first << " Must be < " << tailKey;
    throw IllegalParameterValue(s.str());
  }

  // 查看关键字为the_key的数对是否已经存在,
  // last[i]已经把搜索到the_pair的每一级的最后的节点存储起来
  skipNode<K, E>* theNode = search(the_pair.first);
  if (theNode->element.first == the_pair.first) {
    theNode->element.second = the_pair.second;
    return;
  }

  // 若不存在，确定新节点所在的链表级
  int theLevel = level();
  // levels为当前最大的非空链表级，令theLevel<=levels+1
  // 这样操作就不会弄出很多空链表
  if (theLevel > levels) {
    theLevel = ++levels;  // 最大级数加一，把它放到最大级链表里面
    last[theLevel] = headerNode;
  }

  // 在节点theNode之后插入新节点
  skipNode<K, E>* newNode = new skipNode<K, E>(
      the_pair, theLevel + 1);  // 插入大的时候级数已经确定了，不能改变
  for (int i = 0; i <= theLevel; i++) {  // 插入i级链表
    newNode->next[i] = last[i]->next[i];
    last[i]->next[i] = newNode;
  }

  dSize++;
  return;
};

template <typename K, typename E>
void skipList<K, E>::erase(const K& the_key) {
  // 删除关键字为the_key的数对
  if (the_key >= tailKey) {
    return;  // 没有这样的数对
  }

  // 查看是否有匹配的数对
  skipNode<K, E>* theNode = search(the_key);
  if (theNode->element.first != the_key) return;

  // 从跳表中删除节点()
  for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
    last[i]->next[i] = theNode->next[i];

  // 更新链表级,如果删除了之后最高级的链表为空，则更新最大表级
  while (levels > 0 && headerNode->next[levels] == tailNode) levels--;

  delete theNode;
  dSize--;
};

template <typename K, typename E>
void skipList<K, E>::output(std::ostream& out) const {
  // 讲跳表的数对插入到输出流里面
  for (skipNode<K, E>* currentNode = headerNode->next[0];
       currentNode != tailNode; currentNode = currentNode->next[0])
    out << " <" << currentNode->element.first << " "
        << currentNode->element.second << "> ";
};

// 重载<<
template <typename K, typename E>
std::ostream& operator<<(std::ostream& out, const skipList<K, E>& x) {
  x.output(out);
  return out;
};