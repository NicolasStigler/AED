#include <iostream>
#include <list>
#include <vector>

template <typename K, typename V>
class HashTableChaining {
private:
  std::vector<std::list<std::pair<K, V>>> table;
  int capacity;
  int size;
  const double A = 0.6180339887;

  int hashFunction(K key) const {
    // double fractionalPart = (key * A) - int(key * A);
    // return int(capacity * fractionalPart); // Multiplicacion
    
    return ((a * key + b) % p) % capacity; // Hashing universal
  }

public:
  HashTableChaining(int cap = 10) : capacity(cap), size(0) {
    table.resize(capacity);
  }

  bool isEmpty() const {
    return size == 0;
  }

  void insert(const K& key, const V& value) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
      if (pair.first == key) {
        pair.second = value;
        return;
      }
    }
    table[index].emplace_back(key, value);
    size++;
  }

  V search(const K& key) const {
    int index = hashFunction(key);
    for (const auto& pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::runtime_error("Key not found");
  }

  void deleteItem(const K& key) {
    int index = hashFunction(key);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
      if (it->first == key) {
        chain.erase(it);
        size--;
        return;
      }
    }
    throw std::runtime_error("Key not found");
  }

  void resize(int newCapacity) {
    std::vector<std::list<std::pair<K, V>>> newTable(newCapacity);
    for (const auto& chain : table) {
      for (const auto& pair : chain) {
        int newIndex = std::hash<K>{}(pair.first) % newCapacity;
        newTable[newIndex].emplace_back(pair);
      }
    }
    table = std::move(newTable);
    capacity = newCapacity;
  }
};

int main() {
  HashTableChaining<int, std::string> hashTable(7); // Capacidad inicial de 7
  
  // Insertar elementos
  hashTable.insert(10, "John");
  hashTable.insert(22, "Jane");
  hashTable.insert(31, "Alice");
  hashTable.insert(4, "Bob");

  // Buscar elementos
  try {
    std::cout << "Valor asociado a la clave 10: " << hashTable.search(10) << "\n";
    std::cout << "Valor asociado a la clave 22: " << hashTable.search(22) << "\n";
    std::cout << "Valor asociado a la clave 4: " << hashTable.search(4) << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }

  // Eliminar elemento
  hashTable.deleteItem(22);

  // Intentar buscar un elemento eliminado
  try {
    std::cout << "Valor asociado a la clave 22 despues de eliminar: " << hashTable.search(22) << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }

  // Verificar si la tabla esta vacia
  std::cout << "La tabla esta vacia? " << (hashTable.isEmpty() ? "Si" : "No") << "\n";

  return 0;
}
