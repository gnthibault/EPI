//Compile with g++ --std=c++14 ./kthLargest.cpp -o ./test

#include <iostream>
#include <vector>
#include <cassert>

template<typename T>
T GetKthLargest(std::vector<T> v, int k) {
  //The idea will be to perform a low cost sorting with a pivot
  assert(k<=v.size());
  assert(k>0);

  int64_t start=0,stop=v.size()-1,pivIdx=0;
  while (pivIdx!=k) {
    if (pivIdx>k) {
      pivIdx--; //or random position
      stop=pivIdx;
    } else {
      start = pivIdx;
    }
    T pivot = v[pivIdx];
    std::swap(v[pivIdx],v[stop]);
    //Elements <= v[idx] will be inserted before v[idx]
    int64_t i=start,j=stop;
    while (i<j) {
      if (v[j]<pivot) {
        std::swap(v[j],v[i]);
        i++;
      } else {
        j--;
      }
      //All elements <=pivot are before i index (excluded)
      pivIdx = i;
    }
  }
  return v[pivIdx-1];
}

int main (int argc, char* argv[]) {
  std::vector<int> v{-1,-5,3,2};
  std::cout << "1 Largest elem is " << GetKthLargest(v,1) << std::endl;
  std::cout << "2 Largest elem is " << GetKthLargest(v,2) << std::endl;
  std::cout << "3 Largest elem is " << GetKthLargest(v,3) << std::endl;
  std::cout << "4 Largest elem is " << GetKthLargest(v,4) << std::endl;

  return EXIT_SUCCESS;
}
