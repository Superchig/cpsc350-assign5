#include "TreeNode.h"

class BST {
public:
  BST();
  ~BST();
  // virtual ~BST(); For template class
  void insert(int key, char value); // which in this example is also our key

  // Returns a pointer to a node with the given key
  // Returns nullptr if the key is not found
  TreeNode *search(int key);
  // Returns whether or not the tree has a node with the given key
  bool hasKey(int key);
  bool deleteNode(int k);

  bool isEmpty();
  TreeNode *getMin();
  TreeNode *getMax();

  TreeNode *getSuccessor(TreeNode *d);
  void printTree(TreeNode *node);

  // Print the BST tree from its root
  void printTree();

private:
  TreeNode *root;
};