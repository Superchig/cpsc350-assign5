#include "TreeNode.h"

TreeNode::TreeNode()
{
  key = 0;
  left = nullptr;
  right = nullptr;
}

TreeNode::TreeNode(int k)
{
  key = k;
  left = nullptr;
  right = nullptr;
}

// Left to us to implement
// TODO: Check if correctly implemented
TreeNode::~TreeNode()
{
  if (left) {
    delete left;
  }

  if (right) {
    delete right;
  }
}