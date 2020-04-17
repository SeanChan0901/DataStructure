#pragma once

// 抽像类：边
template <typename T>
class edge {
 public:
  virtual ~edge(){};
  virtual int vertex1() const = 0;  
  virtual int vertex2() const = 0;
  virtual T weight() const = 0;
};