//stl
#include <memory>
#include <tuple>

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
auto GetSmallestValue(std::unique_ptr<BSTNode<T>>& node)
{
  auto s = std::ref(node);
  while(s.get()->left)
  {
    s=std::ref(s.get()->left);
  }
  return s;
}

template<typename T>
BSTNode<T>* DeleteNode(BSTNode<T>* node, T idx)
{
  if (node->m_idx==idx) {
    if (!node->left && !node->right) {
      return nullptr;
    } else if (!node->right) {
      return node->left.release();
    } else if (!node->left) {
      return node->right.release();
    } else {
      //replace by smallest value on right side (it has nothing on its left)
      std::unique_ptr<BSTNode<T>>& s =
        GetSmallestValue(node->right);
      node->m_idx=s->m_idx;
      s.reset(DeleteNode(s.release(),s->m_idx));
      return node;
    }
  } else if (idx < node->m_idx) {
    node->left.reset(DeleteNode(node->left.release(),idx));
    return node;
  } else {
    node->right.reset(DeleteNode(node->right.release(),idx));
    return node;
  }
}

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

  void Delete(T idx) {
    m_rootNode.reset(DeleteNode(m_rootNode.release(),idx));
  }

  void InOrderTraversal() {
    if (m_rootNode) {
      m_rootNode->InOrderPrint();
    }
  }

  BSTNode<T>* GetSuccessor(T idx) {
    BSTNode<T>* best{nullptr};
    if (m_rootNode) {
      std::function<BSTNode<T>* (BSTNode<T>*,BSTNode<T>*,T)> SearchSucc =
        [&](BSTNode<T>* cur, BSTNode<T>* recursiveBest, T idx) {
        BSTNode<T>* best{recursiveBest};
        if (cur->m_idx > idx) {
          if (best) {
            if (cur->m_idx < best->m_idx) {
              best = cur;
            }
          } else {
            best = cur;
          }
          if (cur->left) {
            auto s = SearchSucc(cur->left.get(), best, idx);
            if (s)
              best = s;
          }
        } else {
          if (cur->right) {
            auto s = SearchSucc(cur->right.get(), best, idx);
            if (s)
              best = s;
          }
       }
       return best;
     };
     best = SearchSucc(m_rootNode.get(), best, idx);
    }
    return best;
  }

 protected:
  std::unique_ptr<BSTNode<T>> m_rootNode;
};
