#include "Student.h"

Student::Student()
{
  major = "";
  gpa = -1.0;
  advisor = -1;
}

Student::Student(int studentId, string name, string level, string major,
                 double gpa, int advisor) : Person(studentId, name, level)
{
  this->major = major;
  this->gpa = gpa;
  this->advisor = advisor;
}

void Student::printInfo()
{
  cout << "Student ID: " << getId() << '\n'
       << "\tName: " << getName() << '\n'
       << "\tGrade Level: " << getLevel() << '\n'
       << "\tMajor: " << major << '\n'
       << "\tGPA: " << gpa << '\n'
       << "\tAdvisor ID: " << advisor << '\n';
}

int Student::getAdvisor()
{
  return advisor;
}