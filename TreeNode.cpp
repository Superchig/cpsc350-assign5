#include "TreeNode.h"

TreeNode::TreeNode()
{
  key = 0;
  left = nullptr;
  right = nullptr;
}

TreeNode::TreeNode(int k, char v)
{
  key = k;
  value = v;
  left = nullptr;
  right = nullptr;
}

TreeNode::~TreeNode()
{
  if (left) {
    delete left;
  }

  if (right) {
    delete right;
  }
}