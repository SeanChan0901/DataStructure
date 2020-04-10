#pragma once
template <typename T>
class winnerTree {
 public:
  virtual ~winnerTree(){};
  // 初始化赢者树，接受玩家和玩家数量
  virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;
  // 返回赢者的索引
  virtual int winner() const = 0;
  // 在参赛者thePlayer分数变化后重赛
  virtual void rePlay(int thePlayer) = 0;
};