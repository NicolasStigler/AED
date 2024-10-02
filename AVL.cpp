#include <iostream>
using namespace std;

struct Node {
  int key;
  Node* left;
  Node* right;
  int height;

  Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* n) {
  return n == nullptr ? 0 : n->height;
}

int getBalance(Node* n) {
  if (n == nullptr) return 0;
  return height(n->left) - height(n->right);
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* temp = x->right;

  x->right = y;
  y->left = temp;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* temp = y->left;

  y->left = x;
  x->right = temp;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

Node* insert(Node* node, int key) {
  // Step 1: BST insert
  if (node == nullptr) return new Node(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  // Step 2: Update the height
  node->height = 1 + max(height(node->left), height(node->right));

  // Step 3: Get the balance factor
  int balance = getBalance(node);

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node* minValueNode(Node* node) {
  Node* current = node;

  while (current->left != nullptr)
    current = current->left;

  return current;
}

Node* deleteNode(Node* root, int key) {
  // Step 1: BST delete
  if (root == nullptr) return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      Node* temp = root->left ? root->left : root->right;

      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else
        *root = *temp;
      delete temp;
    } else {
      Node* temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == nullptr) return root;

  // Step 2: Update the height
  root->height = max(height(root->left), height(root->right)) + 1;

  // Step 3: Get the balance factor
  int balance = getBalance(root);

  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void inOrder(Node* root) {
  if (root != nullptr) {
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
  }
}

int main() {
  Node* root = nullptr;

  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);

  cout << "inOrder traversal of AVL tree:" << endl;
  inOrder(root);
  cout << endl;

  root = deleteNode(root, 40);

  cout << "inOrder traversal of AVL tree: (Node 40 deleted)" << endl;
  inOrder(root);
  cout << endl;

  return 0;
}

