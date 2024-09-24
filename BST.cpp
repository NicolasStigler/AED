#include <iostream>

template <typename T>
class BSTree {
private:
  struct NodeBT {
    T data;
    NodeBT *left;
    NodeBT *right;

    NodeBT(T val) : data(val), left(nullptr), right(nullptr) {}
  };

  NodeBT *root;

  void insert(NodeBT *&node, T value) {
    if(node == nullptr)
      node = new NodeBT(value);
    else if(value < node->data)
      insert(node->left, value);
    else
      insert(node->right, value);
  }

  bool search(NodeBT *node, T value) const {
    if(node == nullptr)
      return false;
    if(node->data == value)
      return true;
    return value < node->data ? search(node->left, value) : search(node->right, value);
  }

  void preOrder(NodeBT *node) const {
    if(node != nullptr) {
      std::cout << node->data << " ";
      preOrder(node->left);
      preOrder(node->right);
    }
  }

  void inOrder(NodeBT *node) const {
    if(node != nullptr) {
      inOrder(node->left);
      std::cout << node->data << " ";
      inOrder(node->right);
    }
  }

  void postOrder(NodeBT *node) const {
    if(node != nullptr) {
      preOrder(node->left);
      preOrder(node->right);
      std::cout << node->data << " ";
    }

  }

  void clear(NodeBT *node) {
    if(node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

public:
  BSTree() : root(nullptr) {}

  ~BSTree() {
    clear(root);
  }

  void insert(T value) {
    insert(root, value);
  }

  bool search(T value) const {
    return search(root, value);
  }

  void preOrder() const {
    preOrder(root);
    std::cout << std::endl;
  }

  void inOrder() const {
    inOrder(root);
    std::cout << std::endl;
  }

  void postOrder() const {
    postOrder(root);
    std::cout << std::endl;
  }
};

int main() {
  BSTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  
  std::cout << "In-order traversal: ";
  tree.inOrder();  // Output: 2 3 4 5 7

  std::cout << "Searching for 4: " << (tree.search(4) ? "Found" : "Not found") << std::endl; // Output: Found
  std::cout << "Searching for 8: " << (tree.search(8) ? "Found" : "Not found") << std::endl; // Output: Not found

  return 0;
}

// void BreadthFirstSearch(){
//   Queue<NodeBT*> queue;
//   queue.enqueue(this->root);
//   while(!queue.is_empty()){
//     NodeBT* node = queue.dequeue();
//     std::cout<<node->data<<std::endl;
//     if(node->left != nullptr)
//       queue.enqueue(node->left);
//     if(node->right != nullptr)
//       queue.enqueue(node->right);
//   }
// }

// template<typename F>
// void DepthFirstSearch(F process){
//   Stack<NodeBT*> stack;
//   stack.push(this->root);
//   while(!stack.is_empty()){
//     NodeBT* node = stack.pop();
//     process(node->data);
//     if(node->right != nullptr)
//       stack.push(node->right);
//     if(node->left != nullptr)
//       stack.push(node->left);
//   }
// }
