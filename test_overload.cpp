#include <iostream>
#include "Faculty.h"
#include "Student.h"

using namespace std;

int main(int argc, char **argv)
{
  Faculty *faculty = new Faculty(1001, "Rory Padwell", "Lecturer", "Physics");
  Faculty *faculty2 = new Faculty(1002, "Jim Lorka", "Lecturer", "Mathematics");
  Student *student = new Student(1, "Carl Rimmen", "sophomore", "Physics", 3.3, 1001);
  Student *student2 = new Student(2, "Laura Waxen", "junior", "Chemistry", 3.6, 1002);
  faculty->addAdvisee(student->getId());
  faculty2->addAdvisee(student2->getId());

  cout << "*faculty == *faculty: " << (*faculty == *faculty) << endl;
  cout << "*faculty == *faculty2: " << (*faculty == *faculty2) << endl;

  cout << "*student < *student2: " << (*student < *student2) << endl;
  cout << "*student2 > *student: " << (*student2 > *student) << endl;

  delete faculty;
  delete faculty2;
  delete student;
  delete student2;

  return 0;
}