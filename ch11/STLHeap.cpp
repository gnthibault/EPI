//Compile with g++ --std=c++14 ./STLHeap.cpp -o ./test

#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[]) {
  std::vector<int> v;

  //Max Heap implementation
  std::make_heap(v.begin(),v.end());
  for (auto val : {-1,-5,3,2}) {
    v.push_back(val);
    std::push_heap(v.begin(),v.end());
  }
  std::cout << "Max Heap gives: ";
  while (!v.empty()) {
    std::pop_heap(v.begin(),v.end());
    std::cout << v.back() << ", ";
    v.pop_back();
  }
  std::cout << std::endl;

  //Min Heap implementation
  auto comp = [](int lhs, int rhs) { return lhs > rhs; };
  std::make_heap(v.begin(),v.end(),comp);
  for (auto val : {-1,-5,3,2}) {
    v.push_back(val);
    std::push_heap(v.begin(),v.end(),comp);
  }
  std::cout << "Min Heap gives: ";
  while (!v.empty()) {
    std::pop_heap(v.begin(),v.end(),comp);
    std::cout << v.back() << ", ";
    v.pop_back();
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
