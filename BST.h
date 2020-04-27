#include "TreeNode.h"

class BST {
public:
  BST();
  ~BST();
  // virtual ~BST(); For template class
  void insert(int value); // which in this example is also our key
  bool search(int value);
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