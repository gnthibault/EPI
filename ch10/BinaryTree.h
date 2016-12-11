//stl
#include <memory>

template<typename T>
struct BSTNode {
  BSTNode(T idx):m_idx(idx){}

  T m_idx;
  std::unique_ptr<BSTNode<T>> left;
  std::unique_ptr<BSTNode<T>> right;

  bool Add(T idx) {
    auto addLeaf = [](auto& child, T idx){
      if (child) {
        return child->Add(idx);
      } else {
        child=std::make_unique<BSTNode<T>>(idx);
        return true;
      }
    };

    if (idx < m_idx) {
      return addLeaf(left,idx);
    } else {
      return addLeaf(right,idx);
    }
  }

  void Print() {
    std::cout << m_idx << std::endl;
  }

  void InOrderPrint() {
    if (left) {
      left->InOrderPrint();
    }
    Print();
    if (right) {
      right->InOrderPrint();
    }
  }
};

template<typename T>
class BinaryTree {
 public:
  BinaryTree()=default;
  virtual ~BinaryTree()=default;

  bool Insert(T idx) {
    if(!m_rootNode) {
      m_rootNode=std::make_unique<BSTNode<T>>(idx);
      return true;
    } else {
      return m_rootNode->Add(idx);
    }
  }

  bool Delete(T idx) {
    if (m_rootNode) {
      // rootNode may not contain given idx
      if (m_rootNode->Delete(idx)) {
        return true;
      } else if(m_rootNode->m_idx==idx){ //but it can itself be the node
        m_rootNode.reset();
        return true;
      } else {
        return false;
      }
    } else {
      return true;
    }
  }

  void InOrderTraversal() {
    if (m_rootNode) {
      m_rootNode->InOrderPrint();
    }
  }

 protected:
  std::unique_ptr<BSTNode<T>> m_rootNode;
};
