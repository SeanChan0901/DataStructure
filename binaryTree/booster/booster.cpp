#include "booster.h"

#include <iostream>

#include "linkedBinaryTree/linkedBinaryTree.h"
using namespace std;

// 容忍度
int tolerance = 3;

void placeBoosters(binaryTreeNode<booster>* x) {
  // 计算*x的衰减量，若小于容忍值，则在x的字节点放置一个放大器
  x->element.degradeToLeaf = 0;  // 初始化x处的衰减量

  //  计算x的左子树的衰减量,若大于容忍值则在x的左孩子处放置一个放大器
  binaryTreeNode<booster>* y = x->leftChild;
  if (y != NULL) {
    // x有一棵左子树
    int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
    if (degradation > tolerance) {  // 在x处的衰减量大于容忍值
      // 在y处放置一个放大器
      y->element.boosterHere = true;
      x->element.degradeToLeaf = y->element.degradeFromParent;  // 更新x的衰减量
    } else
      x->element.degradeToLeaf =
          degradation;  // 在x处的衰减量大于容忍值，则更新衰减量
  }
  y = x->rightChild;
  if (y != NULL) {
    // x有一棵右子树
    int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
    if (degradation > tolerance) {  // 在x处的衰减量大于容忍值
      // 在y处放置一个放大器
      y->element.boosterHere = true;
      degradation = y->element.degradeFromParent;  // 更新x的衰减量
    }
    // 对比左右子树衰减量，取最大值作为x的衰减量
    x->element.degradeToLeaf =
        (degradation > x->element.degradeToLeaf ? degradation
                                                : x->element.degradeToLeaf);
  }
}

int main() {
  // test 一棵信号树
  // 测试数据
  booster a, b;
  a.degradeFromParent = 2;
  a.degradeToLeaf = 0;
  a.boosterHere = 0;
  b.degradeFromParent = 1;
  b.degradeToLeaf = 0;
  b.boosterHere = 0;

  linkedBinaryTree<booster> t, u, v, w, x, y;
  u.makeTree(a, x, x);
  v.makeTree(b, u, x);
  u.makeTree(a, x, x);
  w.makeTree(a, u, x);

  b.degradeFromParent = 3;
  u.makeTree(b, v, w);
  v.makeTree(a, x, x);

  b.degradeFromParent = 3;
  w.makeTree(b, x, x);
  y.makeTree(a, v, w);
  w.makeTree(a, x, x);
  t.makeTree(b, y, w);

  b.degradeFromParent = 0;
  v.makeTree(b, t, u);

  // 后缀设置信号放大器
  v.postOrder(placeBoosters);
  // 后缀输出
  // v.postOrderOutput();

  return 0;
}