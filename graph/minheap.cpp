#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MinHeap {
private:
    vector<T> array;
    int size;
    int capacity;

public:
    MinHeap(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->array.resize(capacity);
    }
    
    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < size && array[left] < array[smallest])
            smallest = left;

        if (right < size && array[right] < array[smallest])
            smallest = right;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapify(smallest);
        }
    }

    void buildHeap(const vector<T>& arr) {
        capacity = arr.size();
        size = capacity;
        array = arr;

        for (int i = (size - 1) / 2; i >= 0; --i) {
            heapify(i);
        }
    }

    void insertNode(T value) {
        if (size == capacity) {
            capacity *= 2;
            array.resize(capacity);
        }

        size++;
        int i = size - 1;
        array[i] = value;

        while (i != 0 && array[(i - 1) / 2] > array[i]) {
            swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    T top() {
        if (size <= 0)
            return -1;

        return array[0];
    }

    T pop() {
        if (size <= 0)
            return -1;
        if (size == 1) {
            --size;
            return array[0];
        }

        T root = array[0];
        array[0] = array[size - 1];
        --size;
        heapify(0);
        return root;
    }

    void DeleteNode(T key) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (array[i] == key) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "Key not found" << endl;
            return;
        }

        if (index == size - 1) {
            --size;
            return;
        }

        array[index] = array[size - 1];
        --size;

        heapify(index);
    }

    void printHeap() const {
        for (int i = 0; i < size; ++i)
            cout << array[i] << " ";
        cout << endl;
    }
};

int main() {
    MinHeap<int> minHeap(6);
    vector<int> arr = {15, 10, 5, 4, 3, 2};

    minHeap.buildHeap(arr);

    cout<<"Min Heap built from the array: ";
    minHeap.printHeap();

    minHeap.insertNode(1);
    cout << "Min Heap After inserting the node 1: ";
    minHeap.printHeap();

    cout << "Top value of min Heap: " << minHeap.top() << endl;

    cout << "Minimum Extracted value from Min Heap: " << minHeap.pop() << endl;
    cout << "After extracting Min Heap: ";
    minHeap.printHeap();

    minHeap.DeleteNode(4);
    cout << "After deleting the node 4 from the Min Heap: ";
    minHeap.printHeap();

    return 0;
}
