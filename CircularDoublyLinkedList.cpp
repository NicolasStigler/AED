#include <iostream>

template <typename T>
class CircularDoublyLinkedList {
private:
  struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
  };

  Node* head;
  Node* tail;

public:
  CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}

  ~CircularDoublyLinkedList() {
    clear();
  }

  T front() {
    if (head) return head->data;
    throw std::out_of_range("Lista vacia");
  }

  T back() {
    if (tail) return tail->data;
    throw std::out_of_range("Lista vacia");
  }

  void push_front(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
      head = tail = newNode;
      head->next = head;
      head->prev = head;
    } else {
      newNode->next = head;
      newNode->prev = tail;
      tail->next = newNode;
      head->prev = newNode;
      head = newNode;
    }
  }

  void push_back(T value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
      head = tail = newNode;
      head->next = head;
      head->prev = head;
    } else {
      newNode->next = head;
      newNode->prev = tail;
      tail->next = newNode;
      head->prev = newNode;
      tail = newNode;
    }
  }

  T pop_front() {
    if (head == nullptr) throw std::out_of_range("Lista vacia");
    Node* temp = head;
    T data = head->data;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      tail->next = head->next;
      head->next->prev = tail;
      head = head->next;
    }
    delete temp;
    return data;
  }

  T pop_back() {
    if (tail == nullptr) throw std::out_of_range("Lista vacia");
    Node* temp = tail;
    T data = tail->data;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      tail->prev->next = head;
      head->prev = tail->prev;
      tail = tail->prev;
    }
    delete temp;
    return data;
  }

  void insert(T value, int position) {
    if (position < 0 || position > size()) throw std::out_of_range("Index invalido");
    if (position == 0) {
      push_front(value);
      return;
    }
    if (position == size()) {
      push_back(value);
      return;
    }
    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < position; ++i) {
      current = current->next;
    }
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
  }

  void remove(int position) {
    if (position < 0 || position >= size()) throw std::out_of_range("Index invalido");
    if (position == 0) {
      pop_front();
      return;
    }
    if (position == size() - 1) {
      pop_back();
      return;
    }
    Node* current = head;
    for (int i = 0; i < position; ++i) {
      current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
  }

  T operator[](int position) {
    if (position < 0 || position >= size()) throw std::out_of_range("Index invalido");
    Node* current = head;
    for (int i = 0; i < position; ++i) {
      current = current->next;
    }
    return current->data;
  }

  bool empty() {
    return head == nullptr;
  }

  int size() {
    if (head == nullptr) return 0;
    int count = 0;
    Node* current = head;
    do {
      count++;
      current = current->next;
    } while (current != head);
    return count;
  }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  void reverse() {
    if (head == nullptr) return;
    Node* current = head;
    Node* temp = nullptr;
    do {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    } while (current != head);

    temp = head;
    head = tail;
    tail = temp;
  }
};

int main() {
    CircularDoublyLinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::cout << "Front: " << list.front() << std::endl; // 1
    std::cout << "Back: " << list.back() << std::endl;   // 3

    list.insert(4, 1);  // Inserta 4 en la posicion 1
    std::cout << "Element at 1: " << list[1] << std::endl; // 4

    list.pop_front();  // Elimina el 1
    list.pop_back();   // Elimina el 3

    std::cout << "Size: " << list.size() << std::endl;  // 2

    list.reverse();    // Invierte la lista
    std::cout << "Front after reverse: " << list.front() << std::endl; // 4

    list.clear();  // Limpia la lista
    std::cout << "Is empty: " << list.empty() << std::endl; // 1 (true)

    return 0;
}

