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