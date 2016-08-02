//Local
#include "parity.h"
#include "../../ch4/bithack.h"

//STL
#include <cstdlib>
#include <iostream>
#include <cassert>

typename precomputed_parity::LutType precomputed_parity::LUT = {0};

template<typename T>
struct TestUnsignedParity
{
  static void check( T val )
  {
    auto resNaive = ParityNaive(val);
    auto resDep   = ParityWordDependent(val);
    auto resLUT   = ParityFastLUT(val);
    auto resXor   = ParityXorBased(val);

    assert( resDep==resNaive );
    assert( resLUT==resNaive );
    assert( resXor==resNaive );
  }
};

template<typename T>
struct TestParity
{
  static void check( T val )
  {
    auto resDep   = ParityWordDependent(val);
    auto resLUT   = ParityFastLUT(val);
    auto resXor   = ParityXorBased(val);

    assert( resLUT==resDep );
    assert( resLUT==resXor );
  }
};


//Compile using g++ ./main.cpp -std=c++11 -o ./test
int main( int argc, char* argv[] )
{
  //Initialize the LUT for the fastLUT version
  precomputed_parity::InitializeLUT();

  // Check for many unsigned types only, with multiple values
  performTestWithType<TestUnsignedParity>( std::tuple<unsigned short,
    unsigned int,unsigned long,unsigned long long>() );

  // Check for many signed and unsigned types, with multiple values
  performTestWithType<TestParity>( std::tuple<short,int,long,long long,unsigned short,
    unsigned int,unsigned long,unsigned long long>() );

  return EXIT_SUCCESS;
}
