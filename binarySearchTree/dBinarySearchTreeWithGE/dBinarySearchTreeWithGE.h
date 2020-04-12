#include "binaryTreeNode.h"
#include "dBinarySearchTree.h"

template <typename K, typename E>
class dBinarySearchTreeWithGE : public dBinarySearchTree<K, E> {
 public:
  // 找到一个关键字大于等于theKey而且为最小的数对，返回其指针
  std::pair<const K, E>* findGE(const K& theKey) const;
};

template <class K, class E>
std::pair<const K, E>* dBinarySearchTreeWithGE<K, E>::findGE(const K& theKey)
    const {  // 找到一个关键字大于等于theKey而且为最小的数对，返回其指针
             // 如果没有大于等于theKey的数对，返回NULL
  binaryTreeNode<std::pair<const K, E> >* currentNode = this->root;
  std::pair<const K, E>* bestElement = NULL;  // key最小的数对
                                              // 目前最好的数对
  // search
  while (currentNode != NULL)
    // 是否存在一个更好（符合键值要求的）的数对
    if (currentNode->element.first >= theKey) {  //找到更好的，更新betterElement
      bestElement = &currentNode->element;
      // 继续向下寻找
      currentNode = currentNode->leftChild;
    } else
      // （在左子树）没有找到更好的，从右子树里面找
      currentNode = currentNode->rightChild;

  return bestElement;
};