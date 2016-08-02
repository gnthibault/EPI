//STL
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <random>
#include <limits>
#include <tuple>

#define NB_TEST 4096

/**
The operation x -> x & ~(x-1) return a binary number that contains
1 at the lowest position where there is a one in the original x
*/
template<typename T>
T returnOneAtLowestPosition( T x )
{
  return x & ~(x-1);
}

template<typename T>
T returnOneAtLowestPositionNaive( T x )
{
  size_t bitIdx = 0;
  while( bitIdx < sizeof(T)*8 )
  {
    T val = (x >> bitIdx) & 1;
    if( val == 1 )
      return (T)1 << bitIdx;
    bitIdx++;
  }
  return 0;
}

template<typename T, typename F>
void performNumerousTestWithRandomValues()
{
  //First, check for remarquable values
  F::check( 0 );
  F::check( std::numeric_limits<T>::lowest() );
  F::check( std::numeric_limits<T>::min() );
  F::check( std::numeric_limits<T>::max() );

  //Then gen random uniform distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<T> distribution(
    std::numeric_limits<T>::lowest(),
    std::numeric_limits<T>::max() );

  // Now check for random values
  for( size_t idx = 0; idx<NB_TEST; idx++ )
  {
    F::check( distribution(gen) );
  }
}

template<template <typename> class F, typename T>
void performTestWithType( std::tuple<T> in )
{
  performNumerousTestWithRandomValues<T,F<T>>();
}

template<template <typename> class F, typename T0, typename... Tn>
void performTestWithType( std::tuple<T0,Tn...> in )
{
  performTestWithType<F,T0>( std::tuple<T0>() );
  performTestWithType<F,Tn...>( std::tuple<Tn...>() );
}
