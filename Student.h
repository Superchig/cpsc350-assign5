#include <iostream>

using namespace std;

class Student {
private:
  int studentId;
  string name;
  string level; // Could be "freshman", "sophomore", "junior", or "senior"
  string major;
  double gpa;
  int advisor; // Holds the faculty ID of their advisor

public:
  // Default constructor
  Student();
  // Overloaded constructor
  Student(int studentId, string name, string level, string major, double gpa,
          int advisor);
  
  // Prints all the information for a student
  void printStudent();
};