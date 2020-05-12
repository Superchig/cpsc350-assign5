#include "Person.h"

Person::Person()
{
  id = -1;
  name = "";
  level = "";
}

Person::Person(int id, string name, string level)
{
  this->id = id;
  this->name = name;
  this->level = level;
}

Person::~Person()
{
}

int Person::getId()
{
  return id;
}

string Person::getName()
{
  return name;
}

string Person::getLevel()
{
  return level;
}

void Person::printInfo()
{
}

void Person::setId(int id)
{
  this->id = id;
}

void Person::setName(string name)
{
  this->name = name;
}

void Person::setLevel(string level)
{
  this->level = level;
}