#include <iostream>
#include <vector>
#include <random>

template <typename K, typename V>
class HashTableOpenAddressing {
private:
  struct HashEntry {
    K key;
    V value;
    bool occupied;
    bool deleted;

    HashEntry() : occupied(false), deleted(false) {}
  };

  std::vector<HashEntry> table;
  int capacity;
  int size;
  int a, b;
  const int p = 2147483647;

  int hashFunction(K key) const {
    // double fractionalPart = (key * A) - int(key * A);
    // return int(capacity * fractionalPart); // Multiplicacion
    
    return ((a * key + b) % p) % capacity; // Hashing universal
  }

  int findPosition(const K& key) const {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 1;

    while (table[index].occupied && (table[index].key != key || table[index].deleted)) {
      index = (originalIndex + i * i) % capacity;
      i++;
    }
    return index;
  }

public:
  HashTableOpenAddressing(int cap = 10) : capacity(cap), size(0) {
    table.resize(capacity);
    
    // Generar valores aleatorios para a y b
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, p-1);
    a = dis(gen); // a entre 1 y p-1
    b = dis(gen); // b entre 0 y p-1
  }

  bool isEmpty() const {
    return size == 0;
  }

  void insert(const K& key, const V& value) {
    int index = findPosition(key);
    if (!table[index].occupied || table[index].deleted) {
      table[index].key = key;
      table[index].value = value;
      table[index].occupied = true;
      table[index].deleted = false;
      size++;
    } else {
      table[index].value = value;
    }
  }

  V search(const K& key) const {
    int index = findPosition(key);
    if (!table[index].occupied || table[index].deleted) {
      throw std::runtime_error("Key not found");
    }
    return table[index].value;
  }

  void deleteItem(const K& key) {
    int index = findPosition(key);
    if (!table[index].occupied || table[index].deleted) {
      throw std::runtime_error("Key not found");
    }
    table[index].deleted = true;
    size--;
  }

  void resize(int newCapacity) {
    std::vector<HashEntry> newTable(newCapacity);
    for (const auto& entry : table) {
      if (entry.occupied && !entry.deleted) {
        int newIndex = (a * entry.key + b) % p % newCapacity;
        int i = 1;
        while (newTable[newIndex].occupied) {
          newIndex = (newIndex + i * i) % newCapacity;
          i++;
        }
        newTable[newIndex] = entry;
      }
    }
    table = std::move(newTable);
    capacity = newCapacity;
  }
};

int main() {
  // Crea una tabla hash con Open Addressing
  HashTableOpenAddressing<int, std::string> hashTable(11);

  // Insertar elementos
  hashTable.insert(10, "Alice");
  hashTable.insert(22, "Bob");
  hashTable.insert(31, "Charlie");
  hashTable.insert(4, "Diana");
  
  // Buscar elementos
  try {
    std::cout << "Elemento con clave 10: " << hashTable.search(10) << "\n";
    std::cout << "Elemento con clave 22: " << hashTable.search(22) << "\n";
    std::cout << "Elemento con clave 31: " << hashTable.search(31) << "\n";
    std::cout << "Elemento con clave 4: " << hashTable.search(4) << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }

  // Eliminar un elemento
  hashTable.deleteItem(22);
  try {
    std::cout << "Elemento con clave 22 despues de eliminar: " << hashTable.search(22) << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }

  // Redimensionar la tabla hash
  std::cout << "Redimensionando la tabla...\n";
  hashTable.resize(23);

  // Reinsertar y verificar que los elementos aun existen
  try {
    std::cout << "Elemento con clave 10: " << hashTable.search(10) << "\n";
    std::cout << "Elemento con clave 31: " << hashTable.search(31) << "\n";
    std::cout << "Elemento con clave 4: " << hashTable.search(4) << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
