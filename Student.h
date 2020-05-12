#include "Person.h"
#include <iostream>

using namespace std;

class Student : public Person {
private:
  // Student's level could be "freshman", "sophomore", "junior", or "senior"

  string major;
  double gpa;
  int advisor; // Holds the faculty ID of their advisor

public:
  // Default constructor
  Student();
  // Overloaded constructor
  Student(int studentId, string name, string level, string major, double gpa,
          int advisor);
  
  void printInfo() override;

  // Accessors
  string getMajor();
  double getGpa();
  int getAdvisor();

  // Modifiers
  void setMajor(string major);
  void setGpa(double gpa);
  void setAdvisor(int advisorID);

  // Return a deep copy of this student
  Student *copy();

  // Prompt the user for information about a new Student, then return that Student
  static Student *newFromUser(int studentId);
};

// Obtain an int from user input, checking to make sure that the input is
// actually an int.
// Displays a prompt when asking for user input.
// Placed in Student.h so that Student methods can use it.
int getUserInt(string prompt);

// Obtain a double from user input, checking to make sure that the input is
// actually a double.
// Displays a prompt when asking for user input.
double getUserDouble(string prompt);