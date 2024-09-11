#include <iostream>

template <typename T>
class Stack {
private:
  T* arr;
  int MAX_SIZE;
  int topIndex;

public:
  Stack(int size = 100) : MAX_SIZE(size), topIndex(-1) {
    arr = new T[MAX_SIZE];
  }

  ~Stack() {
    delete[] arr;
  }

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == MAX_SIZE - 1;
  }
  
  T top() const {
    if (isEmpty()) {
      throw std::runtime_error("Stack vacio");
    }
    return arr[topIndex];
  }

  void push(const T& value) {
    if (isFull()) {
      throw std::runtime_error("Stack overflow");
    }
    arr[++topIndex] = value;
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack underflow");
    }
    return arr[topIndex--];
  }

  int size() const {
    return topIndex + 1;
  }
};

// Tests
int main() {
    Stack<int> s(3);

    s.push(10);
    s.push(20);
    s.push(30);
    //s.push(40); // Stack Overflow

    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Top: " << s.top() << std::endl;

    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Popped: " << s.pop() << std::endl;
    std::cout << "Popped: " << s.pop() << std::endl;
    //std::cout << "Popped: " << s.pop() << std::endl; // Stack Underflow

    std::cout << "Size: " << s.size() << std::endl;

    return 0;
}

