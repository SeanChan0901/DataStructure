#include <iostream>
namespace uniteFindWithTreeWeight {
struct unionFindNode {
  bool isRoot;  // 若为真则表示是树的根节点
  int parent;  // 当isRoot为真的时候表示该树的重量，否则表示双亲
  unionFindNode() {
    parent = 1;
    isRoot = true;
  };
};
unionFindNode *node;
void initialize(int numberOfElements) {
  // 初始化numberOfElements棵树，每棵树包含一个元素
  node = new unionFindNode
      [numberOfElements];  // 自动调用默认构造函数构造这么多个元素
}

// 路径紧缩
int find(int theElement) {
  // 返回元素所在树的根
  // 紧缩从元素 theElement到根的路径

  // theRoot最终是树的根
  int theRoot = theElement;
  // 找到树的根 theRoot
  while (!node[theRoot].isRoot) theRoot = node[theRoot].parent;  //网上移一层

  // 紧缩从theElement到root的路径
  int currentNode = theElement;
  while (currentNode != theRoot) {
    int parentNode = node[currentNode].parent;
    node[currentNode].parent = theRoot;  // 移到第二层
    currentNode = parentNode;            // 移到原来的父节点
  }
  return theRoot;
};

void unite(int rootA, int rootB) {
  // 使用重量规则，合并根为不同的两棵树
  if (node[rootA].parent < node[rootB].parent) {
    // 树a成为b的子树
    node[rootB].parent += node[rootA].parent;
    node[rootA].isRoot = false;
    node[rootA].parent = rootB;  // 父节点
  } else {
    // 反之
    node[rootA].parent += node[rootB].parent;
    node[rootB].isRoot = false;
    node[rootB].parent = rootA;  // 父节点
  }
};
}  // namespace uniteFindWithTreeWeight
