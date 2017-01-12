/*
* Compile using  g++ --std=c++11 ./QuickSort.cpp -o ./test
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template<typename T>
void Print(const std::vector<T>& v) {
  std::for_each( v.cbegin(), v.cend(), [](T in) {
    std::cout << in << ","; } );
  std::cout << std::endl;
}

//In place recursive algorithm for O(n log2(n)) sort
template<typename T>
std::vector<T> QuickSort(std::vector<T> in, size_t begin, size_t end) {
  std::vector<T> v(in);
  assert(begin<=end);
  size_t size = end-begin;
  if (size>1) {
    T pivIdx = begin+size/2;//could use rand(begin,end)
    std::swap(v[pivIdx],v[end-1]);
    size_t j=begin;
    for (size_t i=begin; i<end-1; i++) {
      if (v[i]<=v[end-1]) {
        std::swap(v[i],v[j]);
        j++;
      }
    }
    std::swap(v[j],v[end-1]);
    v=QuickSort(v,begin,j);
    v=QuickSort(v,j+1,end);
  }
  return v;
}

int main(int argc, char* argv[])
{
  std::vector<int> v = {-1,5,-9,3,-3,4,4,2};
  Print(QuickSort(v, 0, v.size()));
  std::cout << "--------------" << std::endl;
  return EXIT_SUCCESS;
}
