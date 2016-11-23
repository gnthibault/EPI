//stl
#include <memory>

template<typename T>
struct BinaryTreeNode
{
  T data;
  std::unique_ptr<BinaryTreeNode<T>> left;
  std::unique_ptr<BinaryTreeNode<T>> right;
};
