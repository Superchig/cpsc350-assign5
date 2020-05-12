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
  void printInfo() override;
  // Returns whether or not this faculty member has a student as their advisee
  bool hasAdviseeId(int adviseeId);

  // Accessors
  string getDepartment();
  DoublyLinkedList<int>* getAdviseeIds();

  // Modifiers
  void setDepartment(string department);

  static Faculty* newFromUser(int facultyId);
};