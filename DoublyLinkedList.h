// Header equivalent
#include "ListNode.h"
#include <iostream>

using namespace std;

template <class T>
class DoublyLinkedList {
private:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

public:
  DoublyLinkedList<T>();
  ~DoublyLinkedList<T>();

  void insertFront(T data);
  void insertBack(T data);
  T removeFront();
  // Will return value or position of node depending on implementation.
  int search(T val);
  T remove(T value);
  T removeAtPos(unsigned int pos);

  unsigned int getSize();
  bool isEmpty();
  void printList();

  // Returns the item at front of the list, without removing it
  T getFront();

  // Returns a pointer to the first node
  ListNode<T> *getFrontNode();
};

// Implementation of template class

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  // Empty list
  front = nullptr;
  back = nullptr;
  size = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  // Build some character
  // Just two lines -- I think check for null and then delete
  if (front) {
    delete front;
  }
}

template <class T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
  return (size == 0);
}

template <class T>
void DoublyLinkedList<T>::printList()
{
  ListNode<T> *curr = front;

  while (curr) {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
void DoublyLinkedList<T>::insertFront(T data)
{
  ListNode<T> *node = new ListNode<T>(data);
  // Check if empty
  if (isEmpty()) {
    back = node;
  }
  else {
    // not empty
    node->next = front;
    front->prev = node;
  }
  front = node;
  ++size;
}

template <class T>
void DoublyLinkedList<T>::insertBack(T data)
{
  ListNode<T> *node = new ListNode<T>(data);
  // Check if empty
  if (isEmpty()) {
    front = node;
  }
  else {
    // not empty
    node->prev = back;
    back->next = node;
  }
  back = node;
  ++size;
}

template <class T>
T DoublyLinkedList<T>::removeFront()
{
  if (size <= 0) {
    cerr << "Error: Trying to remove item from list of " << size << " elements." << endl;
  }

  if (front->next) {
    // There is more than one node in the list
    front->next->prev = nullptr;
  }
  else {
    // We have only one node in the list
    back = nullptr;
  }

  ListNode<T> *tmp = front;
  T data = tmp->data;
  front = front->next;
  tmp->next = nullptr;
  delete tmp;

  --size;

  return data;
}

// Need to find the value in the list before we can delete
// This function does not in a position as a parameter
template <class T>
T DoublyLinkedList<T>::remove(T val)
{
  ListNode<T> *curr = front;

  while (curr->data != val) {
    // Keep iterating until we find our value
    curr = curr->next;

    if (!curr) {
      return 0;
    }
  }

  // We've found the value, now let's proceed to delete

  if (curr == front) {
    // Check if node to be deleted is the front
    front = curr->next;
  }
  else {
    // node to be deleted is not the front
    curr->prev->next = curr->next;
  }

  if (curr == back) {
    back = curr->prev;
  }
  else {
    // node to be deleted is not in the back
    curr->next->prev = curr->prev;
  }

  curr->next = nullptr;
  curr->prev = nullptr;
  T data = curr->data;
  delete curr;
  --size;
  return data;
}

template <class T>
int DoublyLinkedList<T>::search(T value)
{
  int position = -1;
  ListNode<T> *curr = front;

  while (curr) {
    // iterate and attempt to find the value
    ++position;

    if (curr->data == value) {
      break;
    }
    else {
      curr = curr->next;
    }
  }

  if (!curr) {
    position = -1; // We did not find the value
  }

  return position;
}

template <class T>
T DoublyLinkedList<T>::removeAtPos(unsigned int pos)
{
  // Custom bounds-checking
  if (pos >= size) {
    cerr << "Error: Trying to remove position " << pos << " from list of size "
         << size << endl;
    return 0;
  }

  unsigned int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while (idx < pos) {
    prev = curr;
    curr = curr->next;

    ++idx;
  }

  prev->next = curr->next;
  curr->next = nullptr;
  T temp = curr->data;
  delete curr;
  --size;

  return temp;
}

template <class T>
T DoublyLinkedList<T>::getFront()
{
  return front->data;
}

template <class T>
ListNode<T> *DoublyLinkedList<T>::getFrontNode()
{
  return front;
}