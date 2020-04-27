#include "BST.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  BST tree;

  tree.insert(10, 'a');
  tree.insert(12, 'b');
  tree.insert(4, 'c');
  tree.insert(22, 'd');

  tree.printTree();

  cout << "Does the tree have node k = 22? " << tree.hasKey(22) << endl;

  cout << "Deleting node k = 22..." << endl;

  tree.deleteNode(22);
  tree.printTree();

  return 0;
}