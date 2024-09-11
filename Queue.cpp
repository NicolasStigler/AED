#include <iostream>

template <typename T>
class Queue {
private:
  T* arr;
  int MAX_SIZE;
  int frontIndex;
  int rearIndex;

public:
  Queue(int size = 100) : MAX_SIZE(size+1), frontIndex(0), rearIndex(0) {
    arr = new T[MAX_SIZE];
  }

  ~Queue() {
    delete[] arr;
  }

  bool isEmpty() const {
    return frontIndex == rearIndex;
  }

  bool isFull() const {
    return (rearIndex + 1) % MAX_SIZE == frontIndex;
  }

  T front() const {
    if (isEmpty()) {
      throw std::runtime_error("Queue vacio");
    }
    return arr[frontIndex];
  }

  void enqueue(T value) {
    if (isFull()) {
      throw std::runtime_error("Queue overflow");
    }
    arr[rearIndex] = value;
    rearIndex = (rearIndex + 1) % MAX_SIZE;
  }

  T dequeue() {
    if (isEmpty()) {
      throw std::runtime_error("Queue underflow");
    }
    T value = arr[frontIndex];
    frontIndex = (frontIndex + 1) % MAX_SIZE;
    return value;
  }

  int size() const {
    return (rearIndex - frontIndex + MAX_SIZE) % MAX_SIZE;
  }
};

// Tests
int main() {
  Queue<int> q(3);

  q.enqueue(10);
  q.enqueue(20);
  q.enqueue(30);
  //q.enqueue(40); // Queue Overflow

  std::cout << "Size: " << q.size() << std::endl;
  std::cout << "Front: " << q.front() << std::endl;

  std::cout << "Dequeued: " << q.dequeue() << std::endl;
  std::cout << "Dequeued: " << q.dequeue() << std::endl;
  std::cout << "Dequeued: " << q.dequeue() << std::endl;
  //std::cout << "Dequeued: " << q.dequeue() << std::endl; // Queue Underflow

  std::cout << "Size: " << q.size() << std::endl;

  return 0;
}

