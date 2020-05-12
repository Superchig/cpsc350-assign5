#include "Student.h"

Student::Student()
{
  major = "";
  gpa = -1.0;
  advisor = -1;
}

Student::Student(int studentId, string name, string level, string major,
                 double gpa, int advisor)
    : Person(studentId, name, level)
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

void Student::setAdvisor(int advisorID)
{
  this->advisor = advisorID;
}

Student *Student::newFromUser(int studentId)
{
  // For obtaining the student id from the user
  // cout << "Input student id: ";
  // string idInput;
  // getline(cin, idInput);
  // int studentId = stoi(idInput);

  cout << "Input name: ";
  string name;
  getline(cin, name);

  string level;
  while (true) {
    cout << "Choose a student level." << '\n'
         << "\tfreshman" << '\n'
         << "\tsophomore" << '\n'
         << "\tjunior" << '\n'
         << "\tsenior" << '\n'
         << "\tgraduate" << endl;
    cout << "Input choice: ";
    getline(cin, level);

    // Make level lowercase
    for (size_t i = 0; i < level.size(); ++i) {
      level.at(i) = tolower(level.at(i));
    }

    // Check if level is valid
    if (level != "freshman" && level != "sophomore" && level != "junior" && level != "senior" && level != "graduate") {
      cout << "That is an invalid student level!" << endl;
      cout << "Try again." << endl;
    }
    else {
      break;
    }
  }

  cout << "Input major: ";
  string major;
  getline(cin, major);

  cout << "Input gpa: ";
  string gpaInput;
  getline(cin, gpaInput);
  double gpa = stod(gpaInput);

  cout << "Input advisor id: ";
  string advisorInput;
  getline(cin, advisorInput);
  double advisorId = stoi(advisorInput);

  Student *result = new Student(studentId, name, level, major, gpa, advisorId);
  return result;
}

string Student::getMajor()
{
  return major;
}

double Student::getGpa()
{
  return gpa;
}

void Student::setMajor(string major)
{
  this->major = major;
}

void Student::setGpa(double gpa)
{
  this->gpa = gpa;
}