#pragma once

#include <iostream>

using namespace std;

class Person {
private:
  int id;
  string name;
  string level;

public:
  Person();
  Person(int id, string name, string level);

  virtual ~Person();

  // Accessors
  int getId();
  string getName();
  string getLevel();

  // Modifiers
  void setId(int id);
  void setName(string name);
  void setLevel(string level);

  // Overload operators
  bool operator==(Person& other);
  bool operator!=(Person& other);
  bool operator<(Person& other);
  bool operator<=(Person& other);
  bool operator>(Person& other);
  bool operator>=(Person& other);

  virtual void printInfo() = 0;
};