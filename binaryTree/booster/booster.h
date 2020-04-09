#pragma once
#include <iostream>

struct booster {
  int degradeToLeaf;      // 到达叶子树时的衰减量
  int degradeFromParent;  // 从双亲节点到该节点的衰减量
  bool boosterHere;       // 是否放置信号放大器

  booster(int theDegradeFromParent) {
    degradeFromParent = theDegradeFromParent;
    degradeToLeaf=0;
  };

  booster() {
    degradeFromParent = 0;
    degradeToLeaf = 0;
  }
  void output(std::ostream& out) const {
    out << boosterHere << " " << degradeToLeaf << " " << degradeFromParent
        << " ";
  };
};

// 重载操作符
std::ostream& operator<<(std::ostream& out, booster x) {
  x.output(out);
  return out;
};
