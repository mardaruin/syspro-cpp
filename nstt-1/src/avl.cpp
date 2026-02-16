#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

struct AVLnode {
  int key;
  int height;
  AVLnode *left_child;
  AVLnode *right_child;

  AVLnode(int k)
      : key(k), height(1), left_child(nullptr), right_child(nullptr) {}
};

class AVLtree {
public:
  AVLtree() : root(nullptr) {}
  ~AVLtree();
  void insert(int value);
  bool search(int value);
  void remove(int value);

private:
  AVLnode *root;

  int height(AVLnode *node) { return node ? node->height : 0; }

  AVLnode *rotateRight(AVLnode *y) {
    AVLnode *x = y->left_child;
    AVLnode *z = x->right_child;
    y->left_child = z;
    x->right_child = y;
    y->height = max(height(y->right_child), height(y->left_child)) + 1;
    x->height = max(height(x->right_child), height(x->left_child)) + 1;
    return x;
  }

  AVLnode *rotateLeft(AVLnode *x) {
    AVLnode *y = x->right_child;
    AVLnode *z = y->left_child;
    y->left_child = x;
    x->right_child = z;
    y->height = max(height(y->right_child), height(y->left_child)) + 1;
    x->height = max(height(x->right_child), height(x->left_child)) + 1;
    return y;
  }

  int balanceFactor(AVLnode *node) {
    if (!node) {
      return 0;
    }
    return height(node->left_child) - height(node->right_child);
  }

  AVLnode *rebalance(AVLnode *node) {
    node->height = 1 + max(height(node->left_child), height(node->right_child));
    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left_child) >= 0) {
      return rotateRight(node);
    }

    if (balance > 1 && balanceFactor(node->left_child) < 0) {
      node->left_child = rotateLeft(node->left_child);
      return rotateRight(node);
    }

    if (balance < -1 && balanceFactor(node->right_child) <= 0) {
      return rotateLeft(node);
    }

    if (balance < -1 && balanceFactor(node->right_child) > 0) {
      node->right_child = rotateRight(node->right_child);
      return rotateLeft(node);
    }

    return node;
  }

  AVLnode *insertHelper(AVLnode *node, int value) {
    if (!node)
      return new AVLnode(value);

    if (value < node->key) {
      node->left_child = insertHelper(node->left_child, value);
    } else {
      node->right_child = insertHelper(node->right_child, value);
    }

    return rebalance(node);
  }

  AVLnode *findMin(AVLnode *node) {
    while (node->left_child != nullptr) {
      node = node->left_child;
    }
    return node;
  }

  AVLnode *deleteHelper(AVLnode *node, int value) {
    if (!node) {
      return node;
    }
    if (node->key < value) {
      node->right_child = deleteHelper(node->right_child, value);
    } else if (node->key > value) {
      node->left_child = deleteHelper(node->left_child, value);
    } else {
      if (!node->left_child || !node->right_child) {
        AVLnode *temp = node->left_child ? node->left_child : node->right_child;
        if (temp == nullptr) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
          delete temp;
        }
      } else {
        AVLnode *minNode = findMin(node->right_child);
        node->key = minNode->key;
        node->right_child = deleteHelper(node->right_child, minNode->key);
      }
    }
    return rebalance(node);
  }

  void clear(AVLnode *node) {
    if (node) {
      clear(node->left_child);
      clear(node->right_child);
      delete node;
    }
  }
};

AVLtree::~AVLtree() { clear(root); }

void AVLtree::insert(int value) { root = insertHelper(root, value); }

void AVLtree::remove(int value) { root = deleteHelper(root, value); }

bool AVLtree::search(int value) {
  AVLnode *curr = root;
  while (curr != nullptr) {
    if (value == curr->key)
      return true;
    if (value < curr->key)
      curr = curr->left_child;
    else
      curr = curr->right_child;
  }
  return false;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}