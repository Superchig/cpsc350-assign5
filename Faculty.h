#include "Person.h"
#include "DoublyLinkedList.h"

class Faculty : public Person {
private:
  // Faculty's level is lecturer, assistant professor, or associate professor

  string department;
  DoublyLinkedList<int>* adviseeIds;

public:
  Faculty();
  Faculty(int id, string name, string level, string department);

  ~Faculty() override;

  void addAdvisee(int adviseeId);

  DoublyLinkedList<int>* getAdviseeIds();

  void printInfo() override;

  static Faculty* newFromUser(int facultyId);
};