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

  // Accessors
  int getId();
  string getName();
  string getLevel();
};