#ifndef myException_
#define myException_

#include <iostream>
#include <string>

// 参数不合法
class IllegalParameterValue {
 public:
  IllegalParameterValue(std::string the_message = "Illegal parameter value") {
    message = the_message;
  };
  void outputMessage() { std::cout << message << std::endl; };

 private:
  std::string message;
};

// 输入数据不合法
class IllegalInputData {
 public:
  IllegalInputData(std::string the_message = "Illegal data input") {
    message = the_message;
  };
  void outputMessage() { std::cout << message << std::endl; };

 private:
  std::string message;
};

// 输入索引不合法
class IllegalIndex {
 public:
  IllegalIndex(std::string the_message = "Illegal index") {
    message = the_message;
  };
  void outputMessage() { std::cout << message << std::endl; };

 private:
  std::string message;
};

// matrix index out of bounds
class matrixIndexOutOfBounds {
 public:
  matrixIndexOutOfBounds(
      std::string theMessage = "Matrix index out of bounds") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// matrix size mismatch
class matrixSizeMismatch {
 public:
  matrixSizeMismatch(
      std::string theMessage = "The size of the two matrics doesn't match") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// stack is empty
class stackEmpty {
 public:
  stackEmpty(std::string theMessage = "Invalid operation on empty stack") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// queue is empty
class queueEmpty {
 public:
  queueEmpty(std::string theMessage = "Invalid operation on empty queue") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// hash table is full
class hashTableFull {
 public:
  hashTableFull(std::string theMessage = "The hash table is full") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// edge weight undefined
class undefinedEdgeWeight {
 public:
  undefinedEdgeWeight(std::string theMessage = "No edge weights defined") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// method undefined
class undefinedMethod {
 public:
  undefinedMethod(std::string theMessage = "This method is undefined") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

#endif