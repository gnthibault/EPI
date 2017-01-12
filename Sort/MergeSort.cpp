/*
* Compile using  g++ --std=c++11 ./MergeSort.cpp -o ./test
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template<typename T>
std::vector<T> Merge(std::vector<T> v0, std::vector<T> v1) {
  assert(v0.size()==v1.size());
  std::vector<T> ret;
  size_t i=0, j=0;
  while (i<v0.size() && j<v1.size()) {
    if (v0[i]<=v1[j]) {
      ret.push_back(v0[i]);
      i++;
    } else {
      ret.push_back(v1[j]);
      j++;
    }
  }
  //Copy residual data
  ret.insert(ret.end(),v0.begin()+i,v0.end());
  ret.insert(ret.end(),v1.begin()+j,v1.end());
  return ret;
}

//A O(n log2(n)) recursive algorithm for sort
//Here, we assume that input vector size is a power of 2
template<typename T>
std::vector<T> MergeSort(std::vector<T> v, size_t begin, size_t end) {
  assert(begin<=end);
  size_t s = end-begin;
  std::vector<T> ret;
  if (s>1) {
    auto v0 = MergeSort(v, begin+0, begin+s/2);
    auto v1 = MergeSort(v, begin+s/2, end);
    return Merge(v0,v1);
  } else {
    return std::vector<T>{v[begin]};
  }
}

template<typename T>
void Print(const std::vector<T>& v) {
  std::for_each( v.cbegin(), v.cend(), [](T in) {
    std::cout << in << ","; } );
  std::cout << std::endl;
}

int main(int argc, char* argv[])
{
  std::vector<int> v = {-1,5,-9,3,-3,4,4,2};
  Print(MergeSort(v,0,v.size()));
  std::cout << "--------------" << std::endl;
  return EXIT_SUCCESS;
}
