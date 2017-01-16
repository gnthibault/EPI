//Compile with g++ --std=c++14 ./STLHeap.cpp -o ./test

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct comparator {
  bool operator()(int i, int j) {
    return i > j;
  }
};

int main(int argc, char const *argv[]) {
  //Min Heap implementation
  std::priority_queue<int, std::vector<int>, comparator> minHeap;
  //Max Heap implementation
  std::priority_queue<int, std::vector<int>> maxHeap;

  for (auto val : {-1,-5,3,2}) {
    minHeap.push(val);
    maxHeap.push(val);
  }

  std::cout << "Min Heap gives: ";
  while (!minHeap.empty()) {
    std::cout << minHeap.top() << ", ";
    minHeap.pop();
  }
  std::cout << std::endl;
  std::cout << "Max Heap gives: ";
  while (!maxHeap.empty()) {
    std::cout << maxHeap.top() << ", ";
    maxHeap.pop();
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
