template <typename K>
class HashTable {
  private:
    static const int TABLE_SIZE = 9; // Tamanio fijo 
    K table[TABLE_SIZE];  // Tabla de hash
    bool occupied[TABLE_SIZE]; // Para marcar las celdas ocupadas

    // Funcion hash simple
    int hashFunction(K key) const {
      return key % TABLE_SIZE;
    }

  public:
    HashTable() {
      for (int i = 0; i < TABLE_SIZE; ++i) {
        occupied[i] = false;
      }
    }

    // Insertar clave en la tabla
    void insert(K key) {
      int hash = hashFunction(key);
      while (occupied[hash]) {
        hash = (hash + 1) % TABLE_SIZE; // Sondeo lineal
      }
      table[hash] = key;
      occupied[hash] = true;
    }

    // Buscar clave en la tabla
    bool find(K key) const {
      int hash = hashFunction(key);
      int initialHash = hash;
      while (occupied[hash]) {
        if (table[hash] == key) return true;
        hash = (hash + 1) % TABLE_SIZE;
        if (hash == initialHash) break;  // Volvimos al punto de inicio
      }
      return false;
    }
};
