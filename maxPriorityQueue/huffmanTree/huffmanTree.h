#pragma once
#include <iostream>

#include "binaryTreeNode.h"
#include "huffmanNode.h"
#include "linkedBinaryTree.h"
#include "minHeap.h"
#include "myExceptions.h"

// 接受一个频率数组（作为权制）参数，一个符号数量参数
template <typename T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n) {
  // 用权值weight[1:n]生成haffmanTree，n>=1
  huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
  linkedBinaryTree<int> emptyTree;
  for (int i = 1; i <= n; i++) {
    hNode[i].weight = weight[i];
    hNode[i].tree = new linkedBinaryTree<int>;
    hNode[i].tree->makeTree(i, emptyTree, emptyTree);
  }

  // 使用一组单节点树构成小根堆
  minHeap<huffmanNode<T> > heap(1);
  heap.initialize(hNode, n);

  // 不断从小根堆中提取两个树合并，直到剩下一棵树
  huffmanNode<T> w, x, y;
  linkedBinaryTree<int>* z;
  // 循环n-1次
  for (int i = 1; i < n; i++) {
    // 从小根堆取出最轻的两棵树
    x = heap.top();  // 这个是复制出来的，要删除
    heap.pop();
    y = heap.top();  // 这个也是复制出来的，要删除
    heap.pop();

    // 合并成一棵树
    z = new linkedBinaryTree<int>;
    z->makeTree(0, *(x.tree), *(y.tree));
    w.weight = x.weight + y.weight;
    w.tree = z;
    heap.push(w);

    // 由于在makeTree的时候两棵子树的根已经指向null(子树已经不存在了)
    delete x.tree;  // 故可以删除掉两棵无用的树
    delete y.tree;
  }
  return heap.top().tree;
};
