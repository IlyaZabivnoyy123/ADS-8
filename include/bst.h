// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(T value) : key(value), count(1),
                            left(nullptr), right(nullptr) {}
  };

  Node* root;

  void add(Node** node, T value) {
    if (*node == nullptr) {
      *node = new Node(value);
      return;
    }

    if (value < (*node)->key) {
      add(&((*node)->left), value);
    } else if (value > (*node)->key) {
      add(&((*node)->right), value);
    } else {
      (*node)->count++;
    }
  }

  int find(Node* node, T value) const {
    if (node == nullptr) return 0;

    if (value == node->key) return node->count;

    if (value < node->key) return find(node->left, value);

    return find(node->right, value);
  }

  int getHeight(Node* node) const {
    if (node == nullptr) return -1;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
  }

  void collect(Node* node, std::vector<std::pair<T, int>>* data) const {
    if (node == nullptr) return;

    collect(node->left, data);
    data->push_back({node->key, node->count});
    collect(node->right, data);
  }

  void destroy(Node* node) {
    if (node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    destroy(root);
  }

  void insert(T value) {
    add(&root, value);
  }

  int search(T value) const {
    return find(root, value);
  }

  int depth() const {
    return getHeight(root);
  }

  std::vector<std::pair<T, int>> getData() const {
    std::vector<std::pair<T, int>> result;
    collect(root, &result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
