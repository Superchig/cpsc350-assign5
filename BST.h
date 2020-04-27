// Template class for a binary search tree

#include "TreeNode.h"
#include <iostream>

using namespace std;

template <class T>
class BST {
public:
  BST();
  ~BST();
  // virtual ~BST(); For template class
  void insert(int key, T value); // which in this example is also our key

  // Returns a pointer to a node with the given key
  // Returns nullptr if the key is not found
  TreeNode<T> *search(int key);
  // Returns whether or not the tree has a node with the given key
  bool hasKey(int key);
  bool deleteNode(int k);

  bool isEmpty();
  TreeNode<T> *getMin();
  TreeNode<T> *getMax();

  TreeNode<T> *getSuccessor(TreeNode<T> *d);
  void printTree(TreeNode<T> *node);

  // Print the BST tree from its root
  void printTree();

private:
  TreeNode<T> *root;
};

template <class T>
BST<T>::BST()
{
  root = nullptr;
}

template <class T>
BST<T>::~BST()
{
  if (root) {
    delete root;
  }
}

template <class T>
void BST<T>::printTree(TreeNode<T> *node)
{
  if (node == nullptr) {
    return;
  }

  printTree(node->left);
  cout << node->key << ": " << node->value << endl;
  printTree(node->right);
}

template <class T>
TreeNode<T> *BST<T>::getMax()
{
  TreeNode<T> *curr = root;

  if (root == nullptr) {
    return nullptr;
  }

  while (curr->right != nullptr) {
    curr = curr->right;
  }

  return curr; // Could return curr->key if we wanted to
}

template <class T>
TreeNode<T> *BST<T>::getMin()
{
  TreeNode<T> *curr = root;

  if (root == nullptr) {
    return nullptr;
  }

  while (curr->left != nullptr) {
    curr = curr->left;
  }

  return curr;
}

template <class T>
bool BST<T>::isEmpty()
{
  return (root == nullptr);
}

template <class T>
void BST<T>::insert(int key, T value)
{
  TreeNode<T> *node =
      new TreeNode<T>(key, value); // value is also the key in our value

  if (root == nullptr) {
    // we have an empty tree
    root = node;
    return;
  }

  // tree is not empty, we need to find the location
  TreeNode<T> *curr = root;
  TreeNode<T> *parent = nullptr;

  while (true) {
    parent = curr;

    // Refactor / check to see if works?
    if (key < curr->key) {
      curr = curr->left;

      // We've reached the end of the tree
      if (curr == nullptr) {
        parent->left = node;
        break;
      }
    }
    else {
      curr = curr->right;

      // We've reached end of tree
      if (curr == nullptr) {
        parent->right = node;
        break;
      }
    }
  }
}

// Normally would search for key
template <class T>
TreeNode<T> *BST<T>::search(int key)
{
  if (isEmpty()) {
    return nullptr;
  }

  // Tree is not empty
  TreeNode<T> *current = root;
  while (current->key != key) {
    if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }

    if (current == nullptr) {
      return nullptr;
    }
  }

  return current;
}

template <class T>
bool BST<T>::hasKey(int key)
{
  if (isEmpty()) {
    return false;
  }

  // Tree is not empty
  TreeNode<T> *current = root;
  while (current->key != key) {
    if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }

    if (current == nullptr) {
      return false;
    }
  }

  return true;
}

template <class T>
bool BST<T>::deleteNode(int k)
{
  if (isEmpty()) {
    return false;
  }
  else if (!hasKey(k)) {
    return false;
  }

  // Tree is not empty so let's look for the value
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;

  // Usual code to find treenode.
  // We will also update pointers
  bool isLeft; // If the current is to the left of its parent
  while (current->key != k) {
    parent = current;
    if (k < current->key) {
      isLeft = true;
      current = current->left;
    }
    else {
      isLeft = false;
      current = current->right;
    }

    if (current == nullptr) {
      return false;
    }
  }

  // If we made it here, then we've found the node now let's proceed to delete
  // it. No children, leaf TreeNode<T>
  if (current->left == nullptr && current->right == nullptr) {
    if (current == root) {
      root = nullptr;
    }
    else if (isLeft) {
      parent->left = nullptr;
    }
    else {
      parent->right = nullptr;
    }

    delete current;
    return true;
  }
  // One child and the child is left
  else if (current->right == nullptr) {
    // does not have a right child

    if (current == root) {
      root = current->left;
    }
    else if (isLeft) {
      parent->left = current->left;
    }
    else {
      parent->right = current->left;
    }

    return true;
  }
  // One child and the child is right
  else if (current->left == nullptr) {
    // does not have a left child

    if (current == root) {
      // root = current->left;
      root = current->right;
    }
    else if (isLeft) {
      parent->left = current->right;
    }
    else {
      parent->right = current->right;
    }

    return true;
  }
  else {
    // The node has 2 children
    TreeNode<T> *successor = getSuccessor(current);

    if (current == root) {
      root = successor;
    }
    else if (isLeft) {
      parent->left = successor;
    }
    else {
      parent->right = successor;
    }

    successor->left = current->left;
    return true;
  }
}

// Will do bulk of pointer updates for deleteNode function
template <class T>
TreeNode<T> *BST<T>::getSuccessor(TreeNode<T> *d)
{
  // d is the node to be deleted
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *current = d->right;

  while (current != nullptr) {
    sp = successor;
    successor = current;
    current = current->left;
  }

  if (successor != d->right) {
    // "Remove successor" by replacing it with its rightmost child
    // If child is null, then sp's new right child is null
    // If child actually had a node, then that becomes sp's new right child
    sp->left = successor->right;
    // Set up successor to replace d by copying d's right node to be its new
    // right node
    successor->right = d->right;
  }

  return successor;
}

template <class T>
void BST<T>::printTree()
{
  printTree(root);
}