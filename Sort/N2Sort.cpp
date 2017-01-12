/*
* Compile using  g++ --std=c++11 ./Bubble.cpp -o ./test
*/

#include <vector>
#include <algorithm>
#include <iostream>

//An inplace algorithm in O(n^2)
template<typename T>
std::vector<T> BubbleSort(std::vector<T> v) {
  for (size_t i=0; i < v.size(); i++) {
    for (size_t j=1; j<v.size()-i; j++) {
      if (v[j-1]>v[j]) {
        std::swap(v[j-1],v[j]);
      }
    }
  }
  return v;
}

//Also an inplace algorithm in O(n^2), kind of the inverse of Bubble Sort
template<typename T>
std::vector<T> InsertSort(std::vector<T> v) {
  for (size_t i=1; i < v.size(); i++) {
    int64_t j=i-1;
    while (v[j]>v[j+1] && j>=0) {
      std::swap(v[j],v[j+1]);
      j--;
    }
  }
  return v;
}

//Also an inplace algorithm in O(n^2), looks like a Bubble Sort but uses only one swap
template<typename T>
std::vector<T> SelectionSort(std::vector<T> v) {
  for (size_t i = 0; i<v.size();i++) {
    T minVal = v[i];
    size_t minIdx = i;
    for (size_t j = i+1; j<v.size(); j++) {
      if (v[j]<minVal) {
        minVal = v[j];
        minIdx = j;
      }
    }
    std::swap(v[minIdx],v[i]);
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
  std::vector<int> v = {-1,5,-9,3,-3,4,4,2,1};
  Print(BubbleSort(v));
  Print(InsertSort(v));
  Print(SelectionSort(v));
  std::cout << "--------------" << std::endl;
  return EXIT_SUCCESS;
}
