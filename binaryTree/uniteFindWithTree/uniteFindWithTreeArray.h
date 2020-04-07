namespace uniteFindWithTreeArray {
int *parent;
void initialize(int numberOfElements) {
  parent = new int[numberOfElements + 1];
  for (int e = 1; e <= numberOfElements; e++) {
    parent[e] = 0;
  }
}  // 初始化在线等价类

int find(int theElement) {
  while (parent[theElement] != 0) theElement = parent[theElement];
  return theElement;
}  // 返回元素theElement所在的树的根（所属等价类）

void unite(int rootA, int rootB) {
  if (rootA != rootB) parent[rootB] = rootA;
}  // 合并两棵根节点不同的树!
}  // namespace uniteFindWithTreeArray
