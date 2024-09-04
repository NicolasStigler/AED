#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
  T data;
  Node* next;
  Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class List {
private:
  Node<T>* head;
  int count;

public:
  List() : head(nullptr), count(0) {}

  ~List() {
    clear();
  }

  T front() {
    if (empty()) throw std::out_of_range("La lista esta vacia");
    return head->data;
  }

  T back() {
    if (empty()) throw std::out_of_range("La lista esta vacia");
    Node<T>* current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    return current->data;
  }

  void push_front(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    count++;
  }

  void push_back(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (empty()) {
      head = newNode;
    } else {
      Node<T>* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }
    count++;
  }

  T pop_front() {
    if (empty()) throw std::out_of_range("La lista esta vacia");
    Node<T>* temp = head;
    T value = head->data;
    head = head->next;
    delete temp;
    count--;
    return value;
  }

  T pop_back() {
    if (empty()) throw std::out_of_range("La lista esta vacia");
    if (head->next == nullptr) {
      T value = head->data;
      delete head;
      head = nullptr;
      count--;
      return value;
    }
    Node<T>* current = head;
    while (current->next->next != nullptr) {
      current = current->next;
    }
    T value = current->next->data;
    delete current->next;
    current->next = nullptr;
    count--;
    return value;
  }

  T operator[](int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Index invalido (oob)");
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    return count;
  }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  void sort() {
    if (count < 2) return;

    for (Node<T>* i = head; i->next != nullptr; i = i->next) {
      for (Node<T>* j = i->next; j != nullptr; j = j->next) {
        if (i->data > j->data) {
          std::swap(i->data, j->data);
        }
      }
    }
  }

  void reverse() {
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
    head = prev;
  }
};



int main() {
  List<int> myList;

  // Testing push_front/push_back
  myList.push_front(10);
  myList.push_back(15);
  myList.push_front(5);
  myList.push_back(20);

  // Testing front/back
  std::cout << "Front: " << myList.front() << std::endl; // Output: 5
  std::cout << "Back: " << myList.back() << std::endl;   // Output: 20

  // Testing operator
  std::cout << "Elemento en index 1: " << myList[1] << std::endl; // Output: 10
  std::cout << "Elemento en index 2: " << myList[2] << std::endl; // Output: 15

  // Testing size
  std::cout << "Size: " << myList.size() << std::endl; // Output: 4

  // Testing pop_front/pop_back
  std::cout << "Pop front: " << myList.pop_front() << std::endl; // Output: 5
  std::cout << "Pop back: " << myList.pop_back() << std::endl;   // Output: 30

  // Testing reverse
  myList.reverse();
  std::cout << "Front (luego del reverse): " << myList.front() << std::endl; // Output: 20

  // Testing sort
  myList.push_back(15);
  myList.push_back(25);
  myList.sort();
  std::cout << "Front (luego del sort): " << myList.front() << std::endl; // Output: 10

  // Testing clear and empty
  myList.clear();
  std::cout << "La lista esta vacia? " << (myList.empty() ? "Si" : "No") << std::endl; // Output: Si

  return 0;
}

