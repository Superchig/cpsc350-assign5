// Template class for the node of a binary search tree

template <class T>
class TreeNode {
public:
  TreeNode();
  // TreeNode(int key);
  TreeNode(int k, T value);
  ~TreeNode();
  // when working with template classes
  // virtual ~TreeNode();

  TreeNode *left;
  TreeNode *right;

  int key;
  T value;
};

template <class T>
TreeNode<T>::TreeNode()
{
  key = 0;
  left = nullptr;
  right = nullptr;
}

template <class T>
TreeNode<T>::TreeNode(int k, T v)
{
  key = k;
  value = v;
  left = nullptr;
  right = nullptr;
}

template <class T>
TreeNode<T>::~TreeNode()
{
  if (left) {
    delete left;
  }

  if (right) {
    delete right;
  }
}