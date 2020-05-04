#include "Person.h"
#include "DoublyLinkedList.h"

class Faculty : public Person {
private:
  // Faculty's level is lecturer, assistant prof, or associate prof

  string department;
  DoublyLinkedList<int>* adviseeIds;

public:
  Faculty();
  Faculty(int id, string name, string level, string department);

  ~Faculty() override;

  void printInfo() override;
};