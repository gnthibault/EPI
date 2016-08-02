//Local
#include "bithack.h"

template<typename T>
struct TestLowest1Bit
{
  static void check( T val )
  {
    assert( returnOneAtLowestPositionNaive(val) ==
            returnOneAtLowestPosition(val) );
  }
};

//Compile using g++ ./main.cpp -std=c++11 -o ./test
int main( int argc, char* argv[] )
{
  // Check for many signed and unsigned types
  performTestWithType<TestLowest1Bit>( std::tuple<short,int,long,long long,unsigned short,
    unsigned int,unsigned long,unsigned long long>() );

  return EXIT_SUCCESS;
}
