#include <iostream>
#include <utility>

#include "linkedBinaryTree/linkedBinaryTree.h"
#include "maxPriorityQueue.h"

// 最大左高树的节点为binaryTreeNode<pair<int ,T>>
// int 存储到外部节点的最短路径,T 为优先级队列元素
template <typename T>
class maxHblt : public maxPriorityQueue<T>,
                public linkedBinaryTree<std::pair<int, T> > {
 public:
  bool empty() const { return this->treeSize == 0; };
  int size() const { return this->treeSize; };
  const T& top() const {
    // 返回最大的优先级别的元素
    if (this->treeSize == 0) throw queueEmpty();
    return this->root->element.second;
  };
  void pop();
  void push(const T&);

  // 初始化左高树
  void initialize(T*, int);

  // 将*this和theHblt合并
  void meld(maxHblt<T>& theHblt) {
    meld(this->root, theHblt->root);
    this->treeSize += theHblt->treeSize;
    theHblt.root = NULL;
    theHblt.treeSize = 0;
  };
  void output() {
    this->postOrder(hbltOutput);
    std::cout << std::endl;
  };

 protected:
  // 组合两棵二叉树
  void meld(binaryTreeNode<std::pair<int, T> >*&,
            binaryTreeNode<std::pair<int, T> >*&);
  // 输出优先级元素
  static void hbltOutput(binaryTreeNode<std::pair<int, T> >* t) {
    std::cout << t->element.second << " ";
  };
};

// 两棵Hblt合并到x上
template <typename T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T> >*& x,
                      binaryTreeNode<std::pair<int, T> >*& y) {
  // 合并分别以*x和*y为根的两棵Hblt
  // 合并后的左高树以x为根，返回x的指针
  if (y == NULL) return;  // y为空
  if (x == NULL) {
    x = y;  //  基本上递归到某个x的右子树为空那么把y合并到x的右子树上
    return;
  }  // x为空

  // x和y都不空，必要时交换x和y
  if (x->element.second < y->element.second) {
    // 交换x和y
    std::swap(x, y);
  }

  // x->element.second>=y->element.second
  meld(x->rightChild, y);

  // 如果有需要交换x的子树，然后设置x->element.first的值
  if (x->leftChild == NULL) {
    // 左子树空，交换左右子树
    x->leftChild = x->rightChild;
    x->rightChild = NULL;
    x->element.first = 1;
  } else {
    // 只有左子树的s的值较小的时候才交换
    if (x->leftChild->element.first < x->rightChild->element.first)
      std::swap(x->leftChild, x->rightChild);
    // 更新x的s值
    x->element.first = x->rightChild->element.first + 1;
  }
};

template <class T>
void maxHblt<T>::push(const T& theElement) {
  // 把元素theElement插入左高树
  // 建立只有一个节点的左高树
  binaryTreeNode<std::pair<int, T> >* q =
      new binaryTreeNode<std::pair<int, T> >(std::pair<int, T>(1, theElement));

  // 将原来的左高树与p合并
  meld(this->root, q);
  this->treeSize++;
};

template <typename T>
void maxHblt<T>::pop() {
  // 删除最大元素
  if (this->root == NULL) throw queueEmpty();

  // 树不空
  binaryTreeNode<std::pair<int, T> >* left = this->root->leftChild;
  binaryTreeNode<std::pair<int, T> >* right = this->root->rightChild;

  delete this->root;
  this->root = left;
  meld(this->root, right);
  this->treeSize--;
};

template <typename T>
void maxHblt<T>::initialize(T* theElement, int theSize) {
  // 用数组theElement【1:theSzie】建立左高树
  //建立一个存储theSize个指向节点的指针的队列
  arrayQueue<binaryTreeNode<std::pair<int, T> >*> q(theSize);
  this->erase();  // 删除本Hblt

  // 初始化树的队列
  for (int i = 1; i <= theSize; i++)
    // 建立只有一个节点的Hblt s(x)=1;
    q.push(new binaryTreeNode<std::pair<int, T> >(
        std::pair<int, T>(1, theElement[i])));

  // 从队列中删除两棵树合并,n个元素只需要合并n-1次
  for (int i = 1; i <= theSize - 1; i++) {
    binaryTreeNode<std::pair<int, T> >* b = q.front();
    q.pop();
    binaryTreeNode<std::pair<int, T> >* c = q.front();
    q.pop();
    meld(b, c);
    q.push(b);
  }
  // 如果初始数组有元素的化，队列必定有元素
  if (theSize > 0) this->root = q.front();
  this->treeSize = theSize;
};