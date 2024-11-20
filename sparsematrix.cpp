#include <iostream>
#include <vector>

template <class T>
class Node {
public:
    T data;
    int pos_row, pos_col;
    Node<T>* next_row;
    Node<T>* next_col;

    Node(int r, int c, T value) : pos_row(r), pos_col(c), data(value), next_row(nullptr), next_col(nullptr) {}
};

template <class T>
class SparseMatrix {
private:
    std::vector<Node<T>*> rows;
    std::vector<Node<T>*> cols;
    int n_rows, n_cols;

public:
    // Constructor
    SparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
        this->rows.resize(rows, nullptr);
        this->cols.resize(cols, nullptr);
    }

    // Destructor
    ~SparseMatrix() {
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                Node<T>* temp = current;
                current = current->next_row;
                delete temp;
            }
        }
    }

    // Insertar un valor en (i, j)
    void insert(int i, int j, T value) {
        if (i >= n_rows || j >= n_cols || i < 0 || j < 0)
            throw std::out_of_range("Invalid index");

        Node<T>* new_node = new Node<T>(i, j, value);

        // Insertar en fila
        if (!rows[i] || rows[i]->pos_col > j) {
            new_node->next_row = rows[i];
            rows[i] = new_node;
        } else {
            Node<T>* current = rows[i];
            while (current->next_row && current->next_row->pos_col < j)
                current = current->next_row;
            new_node->next_row = current->next_row;
            current->next_row = new_node;
        }

        // Insertar en columna
        if (!cols[j] || cols[j]->pos_row > i) {
            new_node->next_col = cols[j];
            cols[j] = new_node;
        } else {
            Node<T>* current = cols[j];
            while (current->next_col && current->next_col->pos_row < i)
                current = current->next_col;
            new_node->next_col = current->next_col;
            current->next_col = new_node;
        }
    }

    // Eliminar un nodo en (i, j)
    void remove(int i, int j) {
        if (i >= n_rows || j >= n_cols || i < 0 || j < 0)
            return;

        // Eliminar de fila
        Node<T>* current = rows[i];
        Node<T>* prev = nullptr;
        while (current && current->pos_col != j) {
            prev = current;
            current = current->next_row;
        }
        if (current) {
            if (prev)
                prev->next_row = current->next_row;
            else
                rows[i] = current->next_row;
        }

        // Eliminar de columna
        current = cols[j];
        prev = nullptr;
        while (current && current->pos_row != i) {
            prev = current;
            current = current->next_col;
        }
        if (current) {
            if (prev)
                prev->next_col = current->next_col;
            else
                cols[j] = current->next_col;
            delete current;
        }
    }

    // Buscar un valor en (i, j)
    T get(int i, int j) const {
        if (i >= n_rows || j >= n_cols || i < 0 || j < 0)
            throw std::out_of_range("Invalid index");

        Node<T>* current = rows[i];
        while (current) {
            if (current->pos_col == j)
                return current->data;
            current = current->next_row;
        }
        return T(); // Retorna valor por defecto si no existe
    }

    // Obtener valor con sobrecarga de operador
    T operator()(int i, int j) const {
        return get(i, j);
    }

    // Comparar dos matrices
    bool operator==(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols)
            return false;

        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            Node<T>* other_current = other.rows[i];

            while (current && other_current) {
                if (current->pos_col != other_current->pos_col || current->data != other_current->data)
                    return false;

                current = current->next_row;
                other_current = other_current->next_row;
            }
            if (current || other_current)
                return false;
        }
        return true;
    }

    // Suma de matrices
    SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols)
            throw std::invalid_argument("Matrix dimensions must match");

        SparseMatrix<T> result(n_rows, n_cols);

        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(i, current->pos_col, current->data);
                current = current->next_row;
            }

            current = other.rows[i];
            while (current) {
                T existing = result.get(i, current->pos_col);
                result.insert(i, current->pos_col, existing + current->data);
                current = current->next_row;
            }
        }
        return result;
    }

    // Restar matrices (puede implementarse similar a la suma)
    SparseMatrix<T> operator-(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols)
            throw std::invalid_argument("Matrix dimensions must match");

        SparseMatrix<T> result(n_rows, n_cols);
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(i, current->pos_col, current->data);
                current = current->next_row;
            }

            current = other.rows[i];
            while (current) {
                T existing = result.get(i, current->pos_col);
                result.insert(i, current->pos_col, existing - current->data);
                current = current->next_row;
            }
        }
        return result;
    }

    // Transpuesta de la matriz
    SparseMatrix<T> transpose() const {
        SparseMatrix<T> result(n_cols, n_rows);
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(current->pos_col, current->pos_row, current->data);
                current = current->next_row;
            }
        }
        return result;
    }
};

int main() {
    SparseMatrix<int> mat(9, 9);
    mat.insert(0, 0, 5);
    mat.insert(3, 2, 8);
    mat.insert(6, 8, 3);

    std::cout << "Elemento en (3,2): " << mat(3, 2) << std::endl;

    auto transpuesta = mat.transpose();
    std::cout << "Elemento en (3,2) de transpuesta: " << transpuesta(3, 2) << std::endl;

    return 0;
}
