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

// Delete a student based off of user input
// Designed to be used for option 8) Delete a student given an id
void deleteStudentFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty)
{
  cout << "Input id of student to delete: ";
  string idInput;
  getline(cin, idInput);

  int studentId;
  try {
    studentId = stoi(idInput);
  }
  catch (invalid_argument& e) {
    cout << "That is not a valid student id!" << endl;
    cout << "No student was deleted." << endl;
    return;
  }

  if (!masterStudent->hasKey(studentId)) {
    cout << "No student has that id!" << endl;
    cout << "No student was deleted." << endl;
    return;
  }
  Student *student = masterStudent->search(studentId)->value;

  // Remove student from advisor's list of advisees
  Faculty *advisor = masterFaculty->search(student->getAdvisor())->value;
  advisor->getAdviseeIds()->remove(studentId);
  cout << "Removed student " << student->getName() << " from advisor " << advisor->getName() << endl;

  // Remove student from tree of Students, deallocate them
  masterStudent->deleteNode(studentId);
  delete student;

  cout << "Student deleted!" << endl;
}

// Delete a faculty member based off of user input
// Should prompt for a new faculty id for the advisees
// Designed to be used for option 9) Delete a faculty member given an id
void deleteFacultyFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty)
{
  cout << "Input id of faculty member to delete: ";
  string idInput;
  getline(cin, idInput);

  int facultyId;
  try {
    facultyId = stoi(idInput);
  }
  catch (invalid_argument& e) {
    cout << "That is not a valid faculty id!" << endl;
    cout << "No faculty member was deleted." << endl;
    return;
  }

  if (!masterFaculty->hasKey(facultyId)) {
    cout << "No faculty member has that id!" << endl;
    cout << "No faculty member was deleted." << endl;
    return;
  }
  Faculty *faculty = masterFaculty->search(facultyId)->value;

  // Update advisees w/ user-specified advisor id
  DoublyLinkedList<int> *advisees = faculty->getAdviseeIds();
  if (!advisees->isEmpty())
  {
    cout << "This advisor has " << advisees->getSize() << " advisees." << endl;
    cout << "Input the new advisor id for these advisees: ";
    string newAdvisorIdInput;
    getline(cin, newAdvisorIdInput);
    int newAdvisorId = stoi(newAdvisorIdInput);

    // Check if new advisor id is valid
    if (!masterFaculty->hasKey(newAdvisorId)) {
      cout << "No faculty member has that id!" << endl;
      cout << "No faculty member was deleted." << endl;
      return;
    }
    Faculty *newAdvisor = masterFaculty->search(newAdvisorId)->value;

    // Iterate over each advisee and update them
    ListNode<int> *curr = advisees->getFrontNode();
    while (curr) {
      Student *advisee = masterStudent->search(curr->data)->value;
      connectPeople(advisee, newAdvisor);

      curr = curr->next;
    }

    cout << "Advisees updated!" << endl;
  }

  // Remove faculty member from tree, deallocate faculty member
  masterFaculty->deleteNode(faculty->getId());
  delete faculty;
}

// Change a student's advisor id based off of user input
// Designed to be used in 11) Change student's advisor given ids
void changeStudAdvFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty)
{
  cout << "Input id of student to modify: ";
  string studentIdInput;
  getline(cin, studentIdInput);
  int studentId = stoi(studentIdInput);

  // Abort if student id is not valid
  if (!masterStudent->hasKey(studentId)) {
    cout << "No student has that id!" << endl;
    cout << "Students were not modified." << endl;
    return;
  }
  
  Student *student = masterStudent->search(studentId)->value;

  cout << "Input id of new advisor for student: ";
  string advisorIdInput;
  getline(cin, advisorIdInput);
  int advisorId = stoi(advisorIdInput);

  // Abort if advisor id is not valid
  if (!masterFaculty->hasKey(advisorId)) {
    cout << "No advisor has that id!" << endl;
    cout << "Students were not modified." << endl;
    return;
  }

  Faculty *oldAdvisor = masterFaculty->search(student->getAdvisor())->value;
  Faculty *newAdvisor = masterFaculty->search(advisorId)->value;

  // Update student to have advisor's id, remove student from old advisor
  oldAdvisor->getAdviseeIds()->remove(studentId);
  connectPeople(student, newAdvisor);
}

int main(int argc, char **argv)
{
  BST<Student *> *masterStudent = new BST<Student *>();
  BST<Faculty *> *masterFaculty = new BST<Faculty *>();

  int studentIdCount = 1; // Equivalent to the most recent student id
  int facultyIdCount = 1; // Equivalent to the most recent faculty id

  Student *defaultStud = new Student(1, "Jim Mij", "freshman", "Business", 3.2, 1);
  Faculty *defaultFac = new Faculty(++facultyIdCount, "John Nhoj", "lecturer", "School of Business");
  Faculty *defaultFac2 = new Faculty(++facultyIdCount, "Carl Lrac", "associate professor", "Physics");
  connectPeople(defaultStud, defaultFac);
  masterStudent->insert(defaultStud->getId(), defaultStud);
  masterFaculty->insert(defaultFac->getId(), defaultFac);
  masterFaculty->insert(defaultFac2->getId(), defaultFac2);

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
    else if (input == "4") { // Find and disply information given the faculty id
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
      if (masterFaculty->hasKey(advisorId)) { // A faculty member has the student's advisor id
        masterStudent->insert(student->getId(), student);
        Faculty *advisor = masterFaculty->search(student->getAdvisor())->value;
        connectPeople(student, advisor);

        cout << "New student created!" << endl;
      }
      else { // No faculty member has id
        cout << "No faculty member has the id: " << advisorId << endl;
        cout << "A new student was not created." << endl;
        delete student;
        --studentIdCount;
      }
    }
    else if (input == "8") { // Delete student given id
      deleteStudentFromUser(masterStudent, masterFaculty);
    }
    else if (input == "9") { // Add new faculty member
      ++facultyIdCount;

      Faculty *faculty = Faculty::newFromUser(facultyIdCount);
      masterFaculty->insert(faculty->getId(), faculty);

      cout << "New faculty member created!" << endl;
    }
    else if (input == "10") { // Delete faculty member given id
      deleteFacultyFromUser(masterStudent, masterFaculty);
    }
    else if (input == "11") { // Change student's advisor given id and new faculty id
      changeStudAdvFromUser(masterStudent, masterFaculty);
    }
    else if (input == "14") { // Exit program
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