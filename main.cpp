#include "BST.h"
#include "Student.h"
#include <iostream>

using namespace std;

void printStudentTree(TreeNode<Student *> *node)
{
  if (!node) {
    return;
  }

  printStudentTree(node->left);
  node->value->printStudent();
}

void printStudentTree(BST<Student *> *tree)
{
  printStudentTree(tree->getRoot());
}

int main(int argc, char **argv)
{
  BST<Student *> *tree = new BST<Student *>();

  Student *stud = new Student();
  tree->insert(1, stud);

  printStudentTree(tree);

  delete tree;
  delete stud;

  return 0;
}