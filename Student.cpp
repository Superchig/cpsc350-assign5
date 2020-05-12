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

  double gpa = getUserDouble("Input gpa: ");

  int advisorId = getUserInt("Input advisor id: ");

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

Student *Student::copy()
{
  Student *studentCopy = new Student(getId(), getName(), getLevel(), getMajor(), getGpa(), getAdvisor());
  return studentCopy;
}

int getUserInt(string prompt)
{
  while (true) {
    cout << prompt;
    string input;
    getline(cin, input);
    int userInt;

    try {
      userInt = stoi(input);
      return userInt;
    }
    catch (invalid_argument &e) {
      cout << "That input was not a valid int value!" << endl;
      cout << "Please try again." << endl;
    }
  }
}

double getUserDouble(string prompt)
{
  while (true) {
    cout << prompt;
    string input;
    getline(cin, input);
    double userDouble;

    try {
      userDouble = stod(input);
      return userDouble;
    }
    catch (invalid_argument &e) {
      cout << "That input was not a valid double value!" << endl;
      cout << "Please try again." << endl;
    }
  }
}