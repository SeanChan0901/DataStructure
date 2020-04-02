#pragma once
#include <iostream>
#include <string>

namespace myHash {  // 用了名空间，防止重名
template <typename K>
class hash;

// 当key为string转化为size_t类型的非负整数
template <>
class hash<std::string> {
 public:
  std::size_t operator()(const std::string theKey) const {
    // 将theKey映射成一个hashValue
    unsigned long hashValue = 0;
    int length = (int)theKey.length();
    for (int i = 0; i < length; i++) {
      hashValue = 5 * hashValue + theKey.at(i);
    }
    return std::size_t(hashValue);
  }
};

// 当key为int时
template <>
class hash<int> {
 public:
  std::size_t operator()(const int theKey) const { return std::size_t(theKey); }
};

// 当key为long的时候

template <>
class hash<long> {
 public:
  std::size_t operator()(const int theKey) const { return std::size_t(theKey); }
};

}  // namespace myHash