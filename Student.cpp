#include "Student.h"

Student::Student()
{
  studentId = -1;
  name = "";
  level = "";
  major = "";
  gpa = -1.0;
  advisor = -1;
}

Student::Student(int studentId, string name, string level, string major,
                 double gpa, int advisor)
{
  this->studentId = studentId;
  this->name = name;
  this->level = level;
  this->major = major;
  this->gpa = gpa;
  this->advisor = advisor;
}

void Student::printStudent()
{
  cout << "Student ID: " << studentId << '\n'
       << "\tName: " << name << '\n'
       << "\tGrade Level: " << level << '\n'
       << "\tMajor: " << major << '\n'
       << "\tGPA: " << gpa << '\n'
       << "\tAdvisor ID: " << advisor << '\n';
}