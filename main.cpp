#include "BST.h"
#include "Faculty.h"
#include "Student.h"
#include <fstream>
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

// Print the information for the advisees of a Faculty based off of user input
// Designed to be used for option 6) given faculty id, print all advisees' info
void printAdviseesFromUser(BST<Faculty *> *masterFaculty, BST<Student *> *masterStudent)
{
  cout << "Input faculty id: ";
  string inputIdStr;
  getline(cin, inputIdStr);
  int inputId = stoi(inputIdStr);

  if (!masterFaculty->hasKey(inputId)) {
    cout << "No faculty member currently has that id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }

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

// Add a student, based off of user input
// Designed to be used for option 7) Add a new student
void addStudentFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty, int &studentIdCount)
{
  if (masterFaculty->isEmpty()) {
    cout << "There are no faculty members, and every student must have a faculty advisor, "
         << "so a student cannot currently be created." << endl;
    cout << "There must be at least 1 faculty member before there can be a student." << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  // Add new student
  ++studentIdCount;

  Student *student = Student::newFromUser(studentIdCount);

  int advisorId = student->getAdvisor();
  // Check that advisorId is valid
  if (!masterFaculty->hasKey(advisorId)) {
    cout << "No faculty member has the id: " << advisorId << endl;
    cout << "Aborting command..." << endl;
    delete student;
    --studentIdCount;

    return;
  }

  masterStudent->insert(student->getId(), student);
  Faculty *advisor = masterFaculty->search(student->getAdvisor())->value;
  connectPeople(student, advisor);

  cout << "New student created!" << endl;
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
  catch (invalid_argument &e) {
    cout << "That is not a valid student id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  if (!masterStudent->hasKey(studentId)) {
    cout << "No student has that id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }
  Student *student = masterStudent->search(studentId)->value;

  // Remove student from advisor's list of advisees
  Faculty *advisor = masterFaculty->search(student->getAdvisor())->value;
  advisor->getAdviseeIds()->remove(studentId);
  cout << "Removed student " << student->getName() << " from advisor " << advisor->getName() << "." << endl;

  // Remove student from tree of Students, deallocate them
  masterStudent->deleteNode(studentId);
  delete student;

  cout << "Student deleted!" << endl;
}

// Delete a faculty member based off of user input
// Should prompt for a new faculty id for the advisees
// Designed to be used for option 10) Delete a faculty member given an id
void deleteFacultyFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty)
{
  cout << "Input id of faculty member to delete: ";
  string idInput;
  getline(cin, idInput);

  int facultyId;
  try {
    facultyId = stoi(idInput);
  }
  catch (invalid_argument &e) {
    cout << "That is not a valid faculty id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  if (!masterFaculty->hasKey(facultyId)) {
    cout << "No faculty member has that id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }
  TreeNode<Faculty *> *facultyNode = masterFaculty->search(facultyId);
  Faculty *faculty = facultyNode->value;

  DoublyLinkedList<int> *advisees = faculty->getAdviseeIds();
  // If this faculty member is the only one, and they have advisees, they can't
  // be deleted, since their advisees would have no new advisor.
  if (facultyNode == masterFaculty->getRoot() && (!facultyNode->left && !facultyNode->right) && !advisees->isEmpty()) {
    cout << "This faculty member is the only one, and they have advisees." << endl;
    cout << "Since students must always have a faculty advisor, and there are no other faculty members, "
         << "this faculty member cannot currently be deleted." << endl;
    cout << "To delete this faculty member, it must have no students or there must be another faculty member." << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  // Update advisees w/ user-specified advisor id
  if (!advisees->isEmpty()) {
    cout << "This advisor has " << advisees->getSize() << " advisees." << endl;
    cout << "Students must always have an advisor, so these advisees need a new advisor." << endl;
    cout << "Input the new advisor id for these advisees: ";
    string newAdvisorIdInput;
    getline(cin, newAdvisorIdInput);
    int newAdvisorId = stoi(newAdvisorIdInput);

    // Check if new advisor id is valid
    if (!masterFaculty->hasKey(newAdvisorId)) {
      cout << "No faculty member has that id!" << endl;
      cout << "Aborting command..." << endl;
      return;
    }
    if (newAdvisorId == facultyId) {
      cout << "The advisees' new advisor cannot be their old advisor." << endl;
      cout << "Aborting command..." << endl;
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
    cout << "Aborting command..." << endl;
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
    cout << "Aborting command..." << endl;
    return;
  }

  Faculty *oldAdvisor = masterFaculty->search(student->getAdvisor())->value;
  Faculty *newAdvisor = masterFaculty->search(advisorId)->value;

  // Update student to have advisor's id, remove student from old advisor
  oldAdvisor->getAdviseeIds()->remove(studentId);
  connectPeople(student, newAdvisor);
  cout << "Student's advisor changed." << endl;
}

// Remove advisee from faculty member given ids
// Designed to be used in 12) remove advisee from faculty member given ids
void removeFacAdviseeFromUser(BST<Student *> *masterStudent, BST<Faculty *> *masterFaculty)
{
  cout << "Input id of faculty member to modify: ";
  string facultyIdInput;
  getline(cin, facultyIdInput);
  int facultyId = stoi(facultyIdInput);

  // Check if faculty id is valid
  if (!masterFaculty->hasKey(facultyId)) {
    cout << "No faculty member has that id." << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  Faculty *faculty = masterFaculty->search(facultyId)->value;

  cout << "Input id of student advisee to remove from faculty: ";
  string adviseeIdInput;
  getline(cin, adviseeIdInput);
  int adviseeId = stoi(adviseeIdInput);

  // Check if faculty member actually has advisee
  if (!faculty->hasAdviseeId(adviseeId)) {
    cout << "Faculty member does not have that student as an advisee!" << endl;
    cout << "Aborting commmand..." << endl;
    return;
  }

  Student *advisee = masterStudent->search(adviseeId)->value;

  cout << "Since the student is no longer an advisee, they need a new advisor." << endl;
  cout << "Input id of student's new faculty advisor: ";
  string newAdvisorIdInput;
  getline(cin, newAdvisorIdInput);
  int newAdvisorId = stoi(newAdvisorIdInput);

  // Check if new advisor id is valid
  if (!masterFaculty->hasKey(newAdvisorId)) {
    cout << "That is not a valid faculty member id!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  if (newAdvisorId == facultyId) {
    cout << "The student's new advisor cannot be their old advisor!" << endl;
    cout << "Aborting command..." << endl;
    return;
  }

  Faculty *newAdvisor = masterFaculty->search(newAdvisorId)->value;

  // Update faculty and student
  faculty->getAdviseeIds()->remove(adviseeId);
  connectPeople(advisee, newAdvisor);
  cout << "Removed advisee from faculty member!" << endl;
}

// Helper function to write a subtree of students into a file
void writeSubStudentsToFile(TreeNode<Student *> *node, ostream &output)
{
  if (!node) {
    return;
  }

  Student *student = node->value;
  writeSubStudentsToFile(node->left, output);
  output << "START_STUDENT\n"
         << "id: " << student->getId() << '\n'
         << "name: " << student->getName() << '\n'
         << "level: " << student->getLevel() << '\n'
         << "major: " << student->getMajor() << '\n'
         << "gpa: " << student->getGpa() << '\n'
         << "advisor: " << student->getAdvisor() << '\n'
         << "END_STUDENT\n";
  writeSubStudentsToFile(node->right, output);
}

// Serialize a tree of Students out to a text file
void writeStudentsToFile(BST<Student *> *masterStudent, string fileName)
{
  ofstream outputFile{fileName};

  writeSubStudentsToFile(masterStudent->getRoot(), outputFile);

  outputFile.close();
}

// Split a string into substrings based off of a delimeter
DoublyLinkedList<string> *split(string str, char delim)
{
  DoublyLinkedList<string> *result = new DoublyLinkedList<string>();
  string buffer;

  for (size_t i = 0; i < str.size(); ++i) {
    char ch = str.at(i);
    if (ch == delim) {
      result->insertBack(buffer);
      buffer.clear();
    }
    else {
      buffer.push_back(ch);
    }
  }
  result->insertBack(buffer);

  return result;
}

// Deserialize a tree of students from a text file
BST<Student *> *readStudentsFromFile(string fileName)
{
  ifstream inputFile{fileName};
  BST<Student *> *masterStudent = new BST<Student *>();

  if (!inputFile.is_open()) {
    return masterStudent;
  }

  string line;
  Student *student = nullptr;
  while (getline(inputFile, line)) {
    if (line == "START_STUDENT") {
      student = new Student();
      continue;
    }
    else if (line == "END_STUDENT") {
      masterStudent->insert(student->getId(), student);
      continue;
    }

    DoublyLinkedList<string> *substrings = split(line, ':');
    string field = substrings->getFront();
    string valueStr = substrings->getFrontNode()->next->data;
    // Remove leading spaces from string
    valueStr.erase(0, valueStr.find_first_not_of(' '));

    if (field == "id") {
      student->setId(stoi(valueStr));
    }
    else if (field == "name") {
      student->setName(valueStr);
    }
    else if (field == "level") {
      student->setLevel(valueStr);
    }
    else if (field == "major") {
      student->setMajor(valueStr);
    }
    else if (field == "gpa") {
      student->setGpa(stod(valueStr));
    }
    else if (field == "advisor") {
      student->setAdvisor(stoi(valueStr));
    }

    delete substrings;
  }

  inputFile.close();

  return masterStudent;
}

// Helper function to write a subtree of faculty members out to a file
void writeSubFacultyToFile(TreeNode<Faculty *> *node, ostream &output)
{
  if (!node) {
    return;
  }

  Faculty *faculty = node->value;
  writeSubFacultyToFile(node->left, output);
  output << "START_FACULTY" << '\n'
         << "id: " << faculty->getId() << '\n'
         << "name: " << faculty->getName() << '\n'
         << "level: " << faculty->getLevel() << '\n'
         << "department: " << faculty->getDepartment() << '\n'
         << "advisees: " << faculty->getAdviseeIds() << '\n'
         << "END_FACULTY\n";
  writeSubFacultyToFile(node->right, output);
}

// Write out a tree of faculty members to a file
void writeFacultyToFile(BST<Faculty *> *masterFaculty, string fileName)
{
  ofstream inputFile{fileName};

  writeSubFacultyToFile(masterFaculty->getRoot(), inputFile);

  inputFile.close();
}

// Take a string which contains ints, separated by spaces, and add those ints to
// a list
void addStringOfIntsToList(DoublyLinkedList<int> *list, string stringOfInts)
{
  DoublyLinkedList<string> *substrings = split(stringOfInts, ' ');

  ListNode<string> *curr = substrings->getFrontNode();
  while (curr) {
    // cout << "curr->data: " << curr->data << endl;
    int studentId = stoi(curr->data);
    list->insertBack(studentId);

    curr = curr->next;
  }

  delete substrings;
}

// Read tree of faculty members in from file. Return empty tree if file cannot
// be opened
BST<Faculty *> *readFacultyFromFile(string fileName)
{
  ifstream inputFile{fileName};
  BST<Faculty *> *masterFaculty = new BST<Faculty *>();

  if (!inputFile.is_open()) {
    return masterFaculty;
  }

  string line;
  Faculty *faculty = nullptr;
  while (getline(inputFile, line)) {
    if (line == "START_FACULTY") {
      faculty = new Faculty();
      continue;
    }
    else if (line == "END_FACULTY") {
      masterFaculty->insert(faculty->getId(), faculty);
      continue;
    }

    DoublyLinkedList<string> *substrings = split(line, ':');
    string field = substrings->getFront();

    string valueStr = substrings->getFrontNode()->next->data;
    // Remove leading spaces from string
    valueStr.erase(0, valueStr.find_first_not_of(' '));

    if (field == "id") {
      faculty->setId(stoi(valueStr));
    }
    else if (field == "name") {
      faculty->setName(valueStr);
    }
    else if (field == "level") {
      faculty->setLevel(valueStr);
    }
    else if (field == "department") {
      faculty->setDepartment(valueStr);
    }
    else if (field == "advisees" && valueStr != "") {
      addStringOfIntsToList(faculty->getAdviseeIds(), valueStr);
    }

    delete substrings;
  }

  return masterFaculty;
}

int main(int argc, char **argv)
{
  BST<Student *> *masterStudent = readStudentsFromFile("studentTable");
  BST<Faculty *> *masterFaculty = readFacultyFromFile("facultyTable");

  // Equivalent to the most recent student id
  int studentIdCount = masterStudent->isEmpty() ? 0 : masterStudent->getMax()->key;
  // Equivalent to the most recent faculty id
  int facultyIdCount = masterFaculty->isEmpty() ? 1000 : masterFaculty->getMax()->key;

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
      printAdviseesFromUser(masterFaculty, masterStudent);
    }
    else if (input == "7") { // Add new student
      addStudentFromUser(masterStudent, masterFaculty, studentIdCount);
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
    else if (input == "12") { // Remove an advisee from a faculty member given ids
      removeFacAdviseeFromUser(masterStudent, masterFaculty);
    }
    else if (input == "14") { // Exit program
      writeStudentsToFile(masterStudent, "studentTable");
      writeFacultyToFile(masterFaculty, "facultyTable");
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