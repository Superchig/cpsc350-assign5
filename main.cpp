#include "BST.h"
#include "Faculty.h"
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

// Helper function for printFacultyTree
void printFacultyTree(TreeNode<Faculty *> *node)
{
  if (!node) {
    return;
  }

  printFacultyTree(node->left);
  node->value->printInfo();
  printFacultyTree(node->right);
}

// Prints out the information for all faculty in a BST
void printFacultyTree(BST<Faculty *> *tree)
{
  printFacultyTree(tree->getRoot());
}

// Deallocates memory for the faculty in a tree
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

// Assign a Faculty to a Student as its advisor, assign the Student to the Faculty
// as an advisee
void connectPeople(Student *advisee, Faculty *advisor)
{
  advisee->setAdvisor(advisor->getId());
  advisor->addAdvisee(advisee->getId());
}

// Print the information for the advisees of a Faculty, given their id
void printAdvisees(BST<Faculty *> *masterFaculty, BST<Student *> *masterStudent, int inputId)
{
  // Print faculty member's advisees
  Faculty *facultyMember = masterFaculty->search(inputId)->value;
  ListNode<int> *curr = facultyMember->getAdviseeIds()->getFrontNode();

  while (curr) {
    int studentId = curr->data;
    Student *student = masterStudent->search(studentId)->value;

    if (student) {
      student->printInfo();
    }
    else {
      cout << "No student has the id " << studentId << '!' << endl;
      break;
    }

    curr = curr->next;
  }
}

int main(int argc, char **argv)
{
  BST<Student *> *masterStudent = new BST<Student *>();
  BST<Faculty *> *masterFaculty = new BST<Faculty *>();

  int studentIdCount = 1; // Equivalent to the most recent student id
  int facultyIdCount = 1; // Equivalent to the most recent faculty id

  Student *defaultStud = new Student(1, "Jim Mij", "freshman", "Business", 3.2, 1);
  Faculty *defaultFac = new Faculty(1, "John Nhoj", "lecturer", "School of Business");
  connectPeople(defaultStud, defaultFac);
  masterStudent->insert(defaultStud->getId(), defaultStud);
  masterFaculty->insert(defaultFac->getId(), defaultFac);

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

    if (input == "1") { // Print all studen tinfo
      printStudentTree(masterStudent);
    }
    else if (input == "2") { // Print all faculty info
      printFacultyTree(masterFaculty);
    }
    else if (input == "3") { // Print student info from id
      cout << "Input student id: ";
      string inputIdStr;
      getline(cin, inputIdStr);
      int inputId = stoi(inputIdStr);

      if (masterStudent->hasKey(inputId)) {
        masterStudent->search(inputId)->value->printInfo();
      }
      else {
        cout << "No student currently has that id!" << endl;
      }
    }
    else if (input == "4") {
      cout << "Input faculty id: ";
      string inputIdStr;
      getline(cin, inputIdStr);
      int inputId = stoi(inputIdStr);

      if (masterFaculty->hasKey(inputId)) {
        masterFaculty->search(inputId)->value->printInfo();
      }
      else {
        cout << "No faculty member currently has that id!" << endl;
      }
    }
    else if (input == "5") { // Print faculty advisor info from student id
      cout << "Input student id: ";
      string inputIdStr;
      getline(cin, inputIdStr);
      int inputId = stoi(inputIdStr);

      if (masterStudent->hasKey(inputId)) { // Found student
        Student *stud = masterStudent->search(inputId)->value;
        int advisorID = stud->getAdvisor();

        if (masterFaculty->hasKey(advisorID)) { // Found faculty
          Faculty *advisor = masterFaculty->search(advisorID)->value;
          advisor->printInfo();
        }
        else { // Could not find faculty
          cout << "This student's faculty id is invalid!" << endl;
        }
      }
      else { // Could not find student
        cout << "No student currently has that id!" << endl;
      }
    }
    else if (input == "6") {
      cout << "Input faculty id: ";
      string inputIdStr;
      getline(cin, inputIdStr);
      int inputId = stoi(inputIdStr);

      printAdvisees(masterFaculty, masterStudent, inputId);
    }
    else if (input == "7") { // Add new student
      ++studentIdCount;

      Student *student = Student::newFromUser(studentIdCount);

      int advisorId = student->getAdvisor();
      if (advisorId == -1 || masterFaculty->hasKey(advisorId)) { // A faculty member has the student's advisor id
        masterStudent->insert(student->getId(), student);
        Faculty *advisor = masterFaculty->search(student->getAdvisor())->value;
        connectPeople(student, advisor);

        cout << "New student created!" << endl;
      }
      else { // No faculty member has id
        cout << "No faculty member has the id: " << advisorId << "!" << endl;
        cout << "A new student was not created." << endl;
        delete student;
        --studentIdCount;
      }
    }
    else if (input == "9") { // Add new faculty member
      ++facultyIdCount;

      Faculty *faculty = Faculty::newFromUser(facultyIdCount);
      masterFaculty->insert(faculty->getId(), faculty);

      cout << "New faculty member created!" << endl;
    }
    else if (input == "14") {
      break;
    }
    else {
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