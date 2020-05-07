#include "Faculty.h"

Faculty::Faculty()
{
  this->department = "";
  this->adviseeIds = new DoublyLinkedList<int>();
}

Faculty::Faculty(int id, string name, string level, string department) : Person(id, name, level)
{
  this->department = department;
  this->adviseeIds = new DoublyLinkedList<int>();
}

Faculty::~Faculty()
{
  delete adviseeIds;
}

void Faculty::printInfo()
{
  cout << "Faculty ID: " << getId() << '\n'
       << "\tName: " << getName() << '\n'
       << "\tLevel: " << getLevel() << '\n'
       << "\tDepartment: " << department << '\n';
  
  cout << "\tAdvisee IDs: ";
  ListNode<int> *curr = adviseeIds->getFrontNode();
  while (curr) {
    cout << curr->data << ' ';

    curr = curr->next;
  }
  cout << endl;
}

void Faculty::addAdvisee(int adviseeId)
{
  adviseeIds->insertBack(adviseeId);
}

DoublyLinkedList<int>* Faculty::getAdviseeIds()
{
  return adviseeIds;
}

Faculty *Faculty::newFromUser(int facultyId)
{
  cout << "Input name: ";
  string name;
  getline(cin, name);

  // Obtain valid faculty level
  string level;
  while (true) {
    cout << "Choose a faculty level." << '\n'
         << "\tlecturer" << '\n'
         << "\tassistant professor" << '\n'
         << "\tassociate professor" << endl;
    cout << "Input choice: ";
    getline(cin, level);

    // Make level lowercase
    for (size_t i = 0; i < level.size(); ++i) {
      level.at(i) = tolower(level.at(i));
    }

    // Check if level is valid
    if (level != "lecturer" && level != "assistant professor" && level != "associate professor") {
      cout << "That is an invalid faculty level!" << endl;
      cout << "Try again." << endl;
    }
    else {
      break;
    }
  }

  cout << "Input department: ";
  string department;
  getline(cin, department);

  Faculty *result = new Faculty(facultyId, name, level, department);
  return result;
}

bool Faculty::hasAdviseeId(int adviseeId)
{
  ListNode<int> *curr = adviseeIds->getFrontNode();

  while (curr) {
    if (curr->data == adviseeId) {
      return true;
    }

    curr = curr->next;
  }

  return false;
}