#pragma once

template <typename T>
class vertexIterator {
 public:
  virtual ~vertexIterator() {}
  virtual int next() = 0;
  virtual int next(T&) = 0;
};