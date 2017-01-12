/*
* Compile using  g++ --std=c++11 ./QuickSort.cpp -o ./test
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

//In place recursive algorithm for O(n log2(n)) sort
template<typename T>
std::vector<T> QuickSort(std::vector<T> in, size_t begin, size_t end) {
  std::vector<T> v = in;
  assert(begin<=end);
  size_t s = end-begin;
  if (s>1) {
    T piv = v.at(begin);
    size_t pivIdx = begin;
    for (size_t i=begin+1; i<end;i++) {
      if (v.at(i)<piv) {
        //std::swap(v[i],v[pivIdx]);
        pivIdx++;
      }
      v=QuickSort(v,begin,pivIdx);
      v=QuickSort(v,pivIdx,end);
    }
  }
  return v;
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
  Print(QuickSort(v, 0, v.size()));
  std::cout << "--------------" << std::endl;
  return EXIT_SUCCESS;
}
