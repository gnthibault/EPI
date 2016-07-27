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

template<typename T>
void performNumerousTestWithRandomValues()
{
  auto check = [](T val){
    assert( returnOneAtLowestPositionNaive(val) ==
            returnOneAtLowestPosition(val) ); };

  //First, check for remarquable values
  check( 0 );
  check( std::numeric_limits<T>::lowest() );
  check( std::numeric_limits<T>::min() );
  check( std::numeric_limits<T>::max() );

  //Then gen random uniform distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<T> distribution(
    std::numeric_limits<T>::lowest(),
    std::numeric_limits<T>::max() );

  // Now check for random values
  for( size_t idx = 0; idx<NB_TEST; idx++ )
  {
    std::cout << ".";
    check( distribution(gen) );
  }
}

template<typename T>
void performTestWithType( std::tuple<T> in )
{
  performNumerousTestWithRandomValues<T>();
}

template<typename T0, typename... Tn>
void performTestWithType( std::tuple<T0,Tn...> in )
{
  performNumerousTestWithRandomValues<T0>();
  performTestWithType( std::tuple<Tn...>() );
}

//Compile using g++ ./bithack.cpp -std=c++11 -o ./test
int main( int argc, char* argv[] )
{
  // Check for many signed and unsigned types
  performTestWithType( std::tuple<short,int,long,long long,unsigned short,
    unsigned int,unsigned long,unsigned long long>() );

  return EXIT_SUCCESS;
}
