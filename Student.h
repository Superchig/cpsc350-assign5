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

  int getAdvisor();
  void setAdvisor(int advisorID);
};