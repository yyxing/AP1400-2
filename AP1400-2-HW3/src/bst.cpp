#include <iomanip>
#include <queue>
#include "bst.h"

BST::Node::Node(int value, BST::Node *left, BST::Node *right) {
  this->value = value;
  this->left = left;
  this->right = right;
}

std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
  os << std::hex << &os << std::dec << "\t=> value:" << node.value
     << "\tleft:" << std::left << std::setw(20) << std::hex << node.left << "\tright:" << node.right << std::dec;
  return os;
}
std::ostream &operator<<(std::ostream &os, BST &bst) {
  std::cout << std::string(82, '*') << std::endl;
  std::queue<BST::Node *> q;
  q.push(bst.get_root());
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    std::cout << *node << std::endl;
    if (node->left)
      q.push(node->left);
    if (node->right)
      q.push(node->right);
  }
  std::cout << std::string(82, '*') << std::endl;
  return os;
}
bool operator>(const BST::Node &node, int a) {
  return node.value > a;
}
bool operator>=(const BST::Node &node, int a) {
  return node.value >= a;
}
bool operator<(const BST::Node &node, int a) {
  return node.value < a;
}
bool operator<=(const BST::Node &node, int a) {
  return node.value <= a;
}
bool operator==(const BST::Node &node, int a) {
  return node.value == a;
}

bool operator>(int a, const BST::Node &node) {
  return a > node.value;
}
bool operator>=(int a, const BST::Node &node) {
  return a >= node.value;
}
bool operator<(int a, const BST::Node &node) {
  return a < node.value;
}
bool operator<=(int a, const BST::Node &node) {
  return a <= node.value;
}
bool operator==(int a, const BST::Node &node) {
  return node.value == a;
}
BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}
BST::Node *&BST::get_root() {
  return this->root;
}
bool BST::add_node(int value) {
  if (root == nullptr) {
    root = new Node(value, nullptr, nullptr);
  } else {
    Node *t = root;
    while (t) {
      if (value > t->value) {
        if (t->right == nullptr) {
          t->right = new Node(value, nullptr, nullptr);
        } else {
          t = t->right;
        }
      } else if (value < t->value) {
        if (t->left == nullptr) {
          t->left = new Node(value, nullptr, nullptr);
        } else {
          t = t->left;
        }
      } else {
        return false;
      }
    }
  }
  return true;
}
void BST::bfs(std::function<void(Node * &)> func) {
  std::queue<Node *> queue;
  if (root == nullptr) return;
  queue.push(root);
  while (!queue.empty()) {
    Node *front = queue.front();
    queue.pop();
    func(front);
    if (front->left) {
      queue.push(front->left);
    }
    if (front->right) {
      queue.push(front->right);
    }
  }
}
size_t BST::length() {
  std::vector<int> values;
  bfs([&values](BST::Node *&node) { values.push_back(node->value); });
  return values.size();
}
BST::Node **BST::find_node(int value) {
  Node *t = root;
  Node *t_root = nullptr;
  while (t) {
    if (value > t->value) {
      t_root = t;
      t = t->right;
    } else if (value < t->value) {
      t_root = t;
      t = t->left;
    } else {
      break;
    }
  }
  if (t) {
    if (t_root->left && t_root->left->value == value) {
      return (&t_root->left);
    } else if (t_root->right && t_root->right->value == value) {
      return (&t_root->right);
    }
  }
  return nullptr;
}
BST::Node **BST::find_parent(int value) {
  Node *t = root;
  Node *t_root = nullptr;
  while (t) {
    if (value > t->value) {
      t_root = t;
      t = t->right;
    } else if (value < t->value) {
      t_root = t;
      t = t->left;
    } else {
      break;
    }
  }
  if (t) {
    return find_node(t_root->value);
  }
  return nullptr;
}
BST::Node **BST::find_successor(int value) {
  Node *node = *find_node(value);
  if (!node) return nullptr;
  node = node->left;
  while (node && node->right) {
    node = node->right;
  }
  return node ? find_node(node->value) : nullptr;
}
bool BST::delete_node(int value) {
  Node **del_node = find_node(value);
  if (!del_node) return false;
  Node **del_root = find_parent(value);
  Node *dr = *del_root;
  Node *dn = *del_node;
  // leaf node
  if (!dn->left) {

  }
  return false;
}
BST::BST(const BST &bst) noexcept {

}
BST::BST(const BST &&bst) noexcept {

}
