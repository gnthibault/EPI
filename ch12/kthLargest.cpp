//Compile with g++ --std=c++14 ./kthLargest.cpp -o ./test

#include <iostream>
#include <vector>

template<typename T>
T GetKthLargest(std::vector<T> v, int k) {

  return v[0];
}

int main (int argc, char* argv[]) {
  std::vector<int> v{-1,-5,3,2};
  std::cout << "1 Largest elem is " << GetKthLargest(v,1) << std::endl;
  std::cout << "2 Largest elem is " << GetKthLargest(v,2) << std::endl;
  std::cout << "3 Largest elem is " << GetKthLargest(v,3) << std::endl;

  return EXIT_SUCCESS;
}
