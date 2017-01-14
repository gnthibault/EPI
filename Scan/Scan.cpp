//Compile using g++ -std=c++11 ./Scan.cpp -fopenmp -o ./test
#include <iostream>
#include <vector>
#include <cassert>
#include <omp.h>

template<typename T>
void Print(const std::vector<T>& v) {
  for( const auto& val : v) {
    std::cout<<val<<",";
  }
  std::cout<<std::endl;
}

/*
* Simple sequential scan
*/
template<template<typename U> class Op, typename T>
std::vector<T> SequentialInclusiveScan(const std::vector<T>& v) {
  assert(v.size()>0);
  std::vector<T> ret(v);
  T acc = Op<T>::identity;
  for(auto it=ret.begin(); it<ret.end(); it++) {
    acc=Op<T>::Op(acc,*it);
    *it=acc;
  }
  return ret;
}

/*
* Hillis & Steele Parallel scan
*/
template<template<typename U> class Op, typename T>
std::vector<T> HillisSteelInclusiveScan(const std::vector<T>& v) {
  assert(v.size()>0);
  std::vector<T> ret(v),tmp(v.size());

  for(size_t n = 1; n<ret.size();n*=2) {
    std::swap(ret,tmp);
    #pragma omp parallel for
    for(size_t i=n; i<ret.size(); i++) {
      ret[i]=Op<T>::Op(tmp[i],tmp[i-n]);
    }
    Print(ret);
  }
  return ret;
}

template<typename T>
class Plus {
public:
  static constexpr T Op(const T& a, const T& b) {
    return a+b;
  }
  static constexpr T identity = (T)0;
};

int main(int argc, char* argv[])
{
  std::vector<int> v{1,-1,4,2,4,-2,-3,5};
  Print(SequentialInclusiveScan<Plus>(v));
  Print(HillisSteelInclusiveScan<Plus>(v));
  return EXIT_SUCCESS;
}
