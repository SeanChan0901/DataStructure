#include <iostream>

#include "binaryTree.h"
#include "binaryTreeNode.h"

template <typename E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> > {
 public:
  // 构造函数和析构函数
  linkedBinaryTree() {
    root = NULL;
    treeSize = 0;
  };
  linkedBinaryTree(binaryTreeNode<E>* theRoot);
  ~linkedBinaryTree() { erase(); };

  // 工具函数
  bool empty() const { return treeSize == 0; };
  int size() const { return treeSize; };

  // 成员遍历函数,接受一个访问函数，按照前序遍历访问
  void preOrder(void (*theVisit)(binaryTreeNode<E>*));
  // 成员遍历函数,接受一个访问函数，按照中序遍历访问
  void inOrder(void (*theVisit)(binaryTreeNode<E>*));
  // 成员遍历函数,接受一个访问函数，按照前后遍历访问
  void postOrder(void (*theVisit)(binaryTreeNode<E>*));
  // 成员遍历函数,接受一个访问函数，按照层次序遍历访问
  void levelOrder(void (*)(binaryTreeNode<E>*));

  void erase() {  // 后续遍历删除一棵树
    postOrder(dispose);
    root = NULL;
    treeSize = 0;
  };

  // 前序输出函数
  void preOrderOutput() {
    preOrder(output);
    std::cout << std::endl;
  };

  // 中序输出函数
  void inOrderOutput() {
    inOrder(output);
    std::cout << std::endl;
  };

  // 后续输出函数
  void postOrderOutput() {
    postOrder(output);
    std::cout << std::endl;
  };

 private:
  binaryTreeNode<E>* root;                      // 根节点
  int treeSize;                                 // 树的节点个数
  static void (*visit)(binaryTreeNode<E>*);     // 访问函数
  static void preOrder(binaryTreeNode<E>* t);   // 前序
  static void inOrder(binaryTreeNode<E>* t);    // 中序
  static void postOrder(binaryTreeNode<E>* t);  // 后序
  static void dispose(binaryTreeNode<E>* t) {
    delete t;
  }  // 删除函数：删除一个节点
  static void output(binaryTreeNode<E>* t) {
    std::cout << t->element << " ";
  };  // 输出函数，输出一个节点
};

template <typename E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);


// 成员遍历函数,接受一个访问函数，按照前序遍历访问
template <typename E>
void linkedBinaryTree<E>::preOrder(void (*theVisit)(binaryTreeNode<E>*)) {
  visit = theVisit;
  preOrder(root);
};
// 成员遍历函数,接受一个访问函数，按照中序遍历访问
template <typename E>
void linkedBinaryTree<E>::inOrder(void (*theVisit)(binaryTreeNode<E>*)) {
  visit = theVisit;
  inOrder(root);
};
// 成员遍历函数,接受一个访问函数，按照前后遍历访问
template <typename E>
void linkedBinaryTree<E>::postOrder(void (*theVisit)(binaryTreeNode<E>*)) {
  visit = theVisit;
  postOrder(root);
};

// 构造函数
template <typename E>
linkedBinaryTree<E>::linkedBinaryTree(binaryTreeNode<E>* theRoot) {
  root = theRoot;
  treeSize = 0;
};

// 前序遍历
template <typename E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t) {
  // 遍历二叉树 *t
  if (t != NULL) {
    linkedBinaryTree<E>::visit(t);  // 访问
    preOrder(t->leftChild);         // 遍历左子树
    preOrder(t->rightChile);        // 遍历右子树
  }
};

//后续遍历
template <typename E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t) {
  // 遍历二叉树t
  if (t != NULL) {
    postOrder(t->leftChild);        // 遍历左子树
    postOrder(t->rightChile);       // 遍历右子树
    linkedBinaryTree<E>::visit(t);  // 访问
  }
};

// 中序遍历
template <typename E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t) {
  if (t != NULL) {
    inOrder(t);                     // 遍历左子树
    linkedBinaryTree<E>::visit(t);  // 访问
    inOrder(t);                     // 遍历右子树
  }
};

// 层次遍历
template <typename E>
void linkedBinaryTree<E>::levelOrder(void (*visit)(binaryTreeNode<E>*)) {
  // 层次遍历二叉树 *t
  binaryTreeNode<E>* t = root;
  arrayQueue<binaryTreeNode<E>*> q;  // 用一个队列来完成
  while (t != NULL) {
    visit(t);

    // 将t的孩子插入队列
    if (t->leftChild != NULL) {
      q.push(t->leftChild);
    }
    if (t->rightChile != NULL) {
      q.push(t->rightChile);
    }

    // 提取下一个要访问的节点
    try {
      t = q.front();
    } catch (queueEmpty()) {
      return;  // 如果队列空则证明遍历完毕
    }
    q.pop();
  }
};