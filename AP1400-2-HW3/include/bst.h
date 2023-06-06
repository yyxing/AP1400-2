#ifndef BST_H
#define BST_H
#include <functional>
#include <iostream>
class BST {
 public:
  class Node;
  BST() = default;
  BST(const BST& bst) noexcept;
  BST(const BST&& bst) noexcept;
  Node *&get_root();
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);
  ~BST();
 private:
  Node *root;
};

class BST::Node {
 public:
  Node(int value, Node *left, Node *right);
  Node() = default;
  Node(const Node &node) = default;

  int value;
  Node *left;
  Node *right;
};
std::ostream &operator<<(std::ostream &os, const BST::Node &node);
std::ostream &operator<<(std::ostream &os, BST &bst);
bool operator>(const BST::Node &node, int a);
bool operator>=(const BST::Node &node, int a);
bool operator<(const BST::Node &node, int a);
bool operator<=(const BST::Node &node, int a);
bool operator==(const BST::Node &node, int a);

bool operator>(int a, const BST::Node &node);
bool operator>=(int a, const BST::Node &node);
bool operator<(int a, const BST::Node &node);
bool operator<=(int a, const BST::Node &node);
bool operator==(int a, const BST::Node &node);


#endif //BST_H