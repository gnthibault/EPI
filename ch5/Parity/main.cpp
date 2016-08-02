//Local
#include "parity.h"

//STL
#include <cstdlib>
#include <iostream>
#include <cassert>

typename precomputed_parity::LutType precomputed_parity::LUT = {0};

//Compile using g++ ./main.cpp -std=c++11 -o ./test
int main( int argc, char* argv[] )
{
  //Initialize the LUT for the fastLUT version
  precomputed_parity::InitializeLUT();

  int sample = 123;

  auto resNaive = ParityNaive(sample);
  auto resDep   = ParityWordDependent(sample);
  auto resLUT   = ParityFastLUT(sample);

  assert( resDep==resNaive );
  assert( resLUT==resNaive );

  return EXIT_SUCCESS;
}
