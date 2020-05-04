// Header equivalent
template <class T>
class ListNode {
public:
  T data;
  ListNode *next;
  ListNode *prev;

  ListNode<T>();      // default constructor
  ListNode<T>(T d); // overloaded constructor
  ~ListNode<T>();
};

// ListNode implementation

template <class T>
ListNode<T>::ListNode()
{
  data = 0;
  next = nullptr;
  prev = nullptr;
}

template <class T>
ListNode<T>::ListNode(T d)
{
  data = d;
  next = nullptr;
  prev = nullptr;
}

template <class T>
ListNode<T>::~ListNode()
{
  // I'll let you do some research
  // AKA build some character

  // Should this delete the following nodes?
  if (next) {
    delete next;
  }
}