#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

template<typename T>
void print( std::vector<T>& in) {
  for(const auto& val : in){
    std::cout << val << ",";
  }
  std::cout<<std::endl;
}

template<typename T>
void findDup( std::vector<T>& arr1, std::vector<T>& arr2, std::vector<T>& dup){
  size_t i=0,j=0;
  while(i<arr1.size() && j<arr2.size())
  {
    if (arr1[i]==arr2[j]) {
      dup.push_back(arr1[i]);
      i++;
      j++;
    } else if (arr1[i]<arr2[j]) {
      i++;
    } else {
      j++;
    }
  }
}

template<typename T>
typename std::vector<T>::const_iterator
  binSearch(const std::vector<T>& large, T val) {
  auto it = large.cbegin();
  int64_t beg = 0;
  int64_t end = large.size()-1;
  while(beg<=end)
  {
    auto mid = (beg+end)/2;
    if (large[mid] < val) {
      beg = mid+1;
    } else if (large[mid] == val) {
      return it+mid;
    } else {
      end = mid-1;
    }
  }
  return large.cend();
}

template<typename T>
void findDup2( std::vector<T>& small, std::vector<T>& large, std::vector<T>& dup){
  for(const auto& val : small) {
    auto res = binSearch(large,val);
    if(res!=large.cend()) {
      dup.push_back(val);
    }
  }
}

template<typename T>
void checkSolution (std::vector<T> dup, std::vector<T> res) {
  assert( res.size()==dup.size());
  assert( std::equal(res.cbegin(),res.cend(),dup.cbegin()));
}

//Compile using g++ -std=c++14 ./test.cpp -o ./test
int main(int argc, char* argv[])
{
  std::vector<int64_t> arr1={-9,-3,0,1,2,3,5,7,18};
  std::vector<int64_t> arr2={-8,-3,1,3,4,6,7,8,9,10,11,18};
  std::vector<int64_t> res={-3,1,3,7,18};
  std::vector<int64_t> dup;
  std::vector<int64_t> dup2;

  //Print inputs
  print(arr1);
  print(arr2);
  print(res);

  //Solution 1
  findDup(arr1,arr2,dup);
  print(dup);
  checkSolution(dup,res);

  //Solution 2
  findDup2(arr1,arr2,dup2);
  print(dup2);
  checkSolution(dup2,res);

  return EXIT_SUCCESS;
}
