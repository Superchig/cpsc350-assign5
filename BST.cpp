#include "BST.h"
#include <iostream>

using namespace std;

BST::BST()
{
  root = nullptr;
}

BST::~BST()
{
  if (root) {
    delete root;
  }
}

void BST::printTree(TreeNode *node)
{
  if (node == nullptr) {
    return;
  }

  printTree(node->left);
  cout << node->key << ": " << node->value << endl;
  printTree(node->right);
}

TreeNode *BST::getMax()
{
  TreeNode *curr = root;

  if (root == nullptr) {
    return nullptr;
  }

  while (curr->right != nullptr) {
    curr = curr->right;
  }

  return curr; // Could return curr->key if we wanted to
}

TreeNode *BST::getMin()
{
  TreeNode *curr = root;

  if (root == nullptr) {
    return nullptr;
  }

  while (curr->left != nullptr) {
    curr = curr->left;
  }

  return curr;
}

bool BST::isEmpty()
{
  return (root == nullptr);
}

void BST::insert(int key, char value)
{
  TreeNode *node =
      new TreeNode(key, value); // value is also the key in our value

  if (root == nullptr) {
    // we have an empty tree
    root = node;
    return;
  }

  // tree is not empty, we need to find the location
  TreeNode *curr = root;
  TreeNode *parent = nullptr;

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
TreeNode *BST::search(int key)
{
  if (isEmpty()) {
    return nullptr;
  }

  // Tree is not empty
  TreeNode *current = root;
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

bool BST::hasKey(int key)
{
  if (isEmpty()) {
    return false;
  }

  // Tree is not empty
  TreeNode *current = root;
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

bool BST::deleteNode(int k)
{
  if (isEmpty()) {
    return false;
  }
  else if (!hasKey(k)) {
    return false;
  }

  // Tree is not empty so let's look for the value
  TreeNode *current = root;
  TreeNode *parent = root;

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
  // it. No children, leaf TreeNode
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
    TreeNode *successor = getSuccessor(current);

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
TreeNode *BST::getSuccessor(TreeNode *d)
{
  // d is the node to be deleted
  TreeNode *sp = d;
  TreeNode *successor = d;
  TreeNode *current = d->right;

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

void BST::printTree()
{
  printTree(root);
}