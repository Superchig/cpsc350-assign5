#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>

using namespace std;

// Helper function for printing all students in a BST
void printStudentTree(TreeNode<Student *> *node)
{
  if (!node) {
    return;
  }

  printStudentTree(node->left);
  node->value->printInfo();
  printStudentTree(node->right);
}

// Print out the information for all students in BST
void printStudentTree(BST<Student *> *tree)
{
  printStudentTree(tree->getRoot());
}

// Helper function for deallocating the students in a BST
void deallocateStudents(TreeNode<Student *> *node)
{
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

void printFacultyTree(TreeNode<Faculty *> *node)
{
  if (!node) {
    return;
  }

  printFacultyTree(node->left);
  node->value->printInfo();
  printFacultyTree(node->right);
}

void printFacultyTree(BST<Faculty *> *tree)
{
  printFacultyTree(tree->getRoot());
}

void deallocateFaculty(TreeNode<Faculty *> *node)
{
  if (node->left) {
    deallocateFaculty(node->left);
  }
  if (node->right) {
    deallocateFaculty(node->right);
  }

  delete node->value;
}

void deallocateFaculty(BST<Faculty *> *tree)
{
  if (tree->isEmpty()) {
    return;
  }

  deallocateFaculty(tree->getRoot());
}

int main(int argc, char **argv)
{
  BST<Student *> *masterStudent = new BST<Student *>();
  BST<Faculty *> *masterFaculty = new BST<Faculty *>();

  Student *stud = new Student(1, "Jim Mij", "Freshman", "Business", 3.2, -1);
  masterStudent->insert(stud->getId(), stud);
  masterFaculty->insert(1, new Faculty());

  // Main user input loop
  while (true) {
    string input;

    cout << "---- Choices ----" << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << '\n'
         << "2. Print all faculty and their information (sorted by ascending id #)" << '\n'
         << "3. Find and display student information given the students id" << '\n'
         << "4. Find and display faculty information given the faculty id" << '\n'
         << "5. Given a student’s id, print the name and info of their faculty advisor" << '\n'
         << "6. Given a faculty id, print ALL the names and info of his/her advisees." << '\n'
         << "7. Add a new student" << '\n'
         << "8. Delete a student given the id" << '\n'
         << "9. Add a new faculty member" << '\n'
         << "10. Delete a faculty member given the id." << '\n'
         << "11. Change a student’s advisor given the student id and the new faculty id." << '\n'
         << "12. Remove an advisee from a faculty member given the ids" << '\n'
         << "13. Rollback" << '\n'
         << "14. Exit" << '\n';

    cout << "> ";

    getline(cin, input);

    if (input == "1") {
      printStudentTree(masterStudent);
    } else if (input == "2") {
      printFacultyTree(masterFaculty);
    } else if (input == "14") {
      break;
    } else {
      cout << "Sorry, that input is currently either invalid or not implemented yet." << endl;
    }
    
    cout << "Press enter to continue..." << endl;
    string unused;
    getline(cin, unused);
  }

  // Deallocate students and delete trees
  deallocateStudents(masterStudent);
  delete masterStudent;

  deallocateFaculty(masterFaculty);
  delete masterFaculty;

  return 0;
}