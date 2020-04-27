#include "BST.h"
#include "Student.h"
#include <iostream>

using namespace std;

// Helper function for printing all students in a BST
void printStudentTree(TreeNode<Student *> *node)
{
  if (!node) {
    return;
  }

  printStudentTree(node->left);
  node->value->printStudent();
}

// Print out the information for all students in BST
void printStudentTree(BST<Student *> *tree)
{
  printStudentTree(tree->getRoot());
}

// Helper function for deallocating the students in a BST
void deallocateStudents(TreeNode<Student *> *node) {
  if (node->left) {
    deallocateStudents(node->left);
  }
  if (node->right) {
    deallocateStudents(node->right);
  }
  delete node->value;
}

// Deallocate the memory for the Student objects (not the nodes) in a BST
void deallocateStudents(BST<Student *> *tree)
{
  if (tree->isEmpty()) {
    return;
  }

  deallocateStudents(tree->getRoot());
}

int main(int argc, char **argv)
{
  BST<Student *> *tree = new BST<Student *>();

  Student *stud = new Student();
  tree->insert(1, stud);

  printStudentTree(tree);

  deallocateStudents(tree);
  delete tree;

  return 0;
}