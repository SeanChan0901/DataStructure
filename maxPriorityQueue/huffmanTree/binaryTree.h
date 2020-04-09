#pragma once
template <typename T>
class binaryTree {
 public:
  virtual ~binaryTree() {}
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  // 接受的参数为一个函数
  // 该函数的格式为：1）返回类型为void 2)接受一个T类型的指针
  // 这个函数由一个函数指针*来访问
  virtual void preOrder(void (*)(T*)) = 0;    // 前序遍历
  virtual void inOrder(void (*)(T*)) = 0;     // 中序遍历
  virtual void postOrder(void (*)(T*)) = 0;   // 后续遍历
  virtual void levelOrder(void (*)(T*)) = 0;  // 层次遍历
};