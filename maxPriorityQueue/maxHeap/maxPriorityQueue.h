// 优先级队列的抽象类
template <typename T>
class maxPriorityQueue {
 public:
  virtual ~maxPriorityQueue(){};  
  virtual bool empty() const = 0;  // 判断队列是否为空
  virtual int size() const = 0;  // 返回队列元素个数
  virtual const T& top() const = 0;  // 返回优先级最大的元素
  virtual void pop() = 0;  // 删除优先级最大的元素
  virtual void push(const T& theElement) = 0;  // 插入一个元素theElement
};