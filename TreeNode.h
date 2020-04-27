class TreeNode {
public:
  TreeNode();
  // TreeNode(int key);
  TreeNode(int k, char value);
  ~TreeNode();
  // when working with template classes
  // virtual ~TreeNode();

  TreeNode *left;
  TreeNode *right;

  int key;
  char value;
};