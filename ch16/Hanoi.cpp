//Compile using g++ --std=c++14 ./Hanoi.cpp -o ./test
#include <iostream>
#include <list>
#include <array>
#include <cassert>
#include <numeric>

template<typename T>
void Print(const std::list<T>& l) {
  for (const auto& val : l) {
    std::cout << val << ",";
  }
  std::cout << std::endl;
}

template<typename T>
bool CheckPeg(const std::list<T>& l) {
   bool isOK = true;
   for (auto it = std::next(l.cbegin()); it!=l.cend(); it++) {
     isOK &= *std::prev(it)<=*it;
   }
   return isOK;
}

template<typename T>
void PopLastElem(std::list<T>& src, std::list<T>& tmp) {
  assert(CheckPeg(src)&&CheckPeg(tmp));
  if (!src.empty()) {
    tmp.push_front(src.front());
    src.pop_front();
  }
  assert(CheckPeg(src)&&CheckPeg(tmp));
}


template<typename T>
class HanoiTower {
public:
  HanoiTower(size_t n) {
    pegs[0]=std::list<T>(n);
    std::iota(pegs[0].begin(),pegs[0].end(),1);
  }

  void PerformHanoi() {
    Reconstruct(pegs[0],pegs[1],pegs[2],pegs[0].size(),0);
  }

  void Check() {
    std::cout<<"Peg 1 (should be blank) : ";
    Print(pegs[0]);
    std::cout<<"Peg 2 (should be sorted) : ";
    Print(pegs[1]);
    std::cout<<"Peg 3 (should be blank) : ";
    Print(pegs[2]);
  }

  void Reconstruct(std::list<T>& src, std::list<T>& dst ,std::list<T>& tmp,
                    int remain, int done) {
    if (remain>0) {
      //Pop top element from src, and put on tmp
      PopLastElem(src,tmp);
      //Transfer dst on top of src
      Reconstruct(dst,src,tmp,done,0);
      //Pop top element from tmp, and put on dst
      PopLastElem(tmp,dst);
      //Transfer the previous storage from src to dst
      Reconstruct(src,dst,tmp,done,0);
      //Next step
      Reconstruct(src,dst,tmp,remain-1,done+1);

    }
  }

protected:
  std::array<std::list<T>,3> pegs;
};

int main(int argc, char* argv[]) {
  HanoiTower<int> t(10);
  t.PerformHanoi();
  t.Check();
  return EXIT_SUCCESS;
}
