
//STL
#include <array>
#include <cmath>

#define WORDSIZEBYTE 2
#define WORDMASK 0xFF
#define WORDSIZEBIT WORDSIZEBYTE*8

//First solution : naive test for all bits
template<typename T>
short ParityNaive( T x )
{
  short result = 0;
  while(x)
  {
    result += ( x & 1 ); //Add 1 if 1-bit is detected
    x >>= 1; //shift word to the right, to check next bit
  }
  return result % 2;
}

//Second solution : use the trick from chapter 4, commplexity now depends on
//the number of 1-bit in the word, and is equal to the naive case in the worst
//case
template<typename T>
short ParityWordDependent( T x )
{
  short result = 0;
  while(x) //While all 1-bit haven't been droppped
  {
    result ^= 1; //bitwise xor to alternate between 0 and 1
    x &= (x-1); //Drop the lowest 1-bit of x
  }
  return result;
}

//Stores the 16bit lookup table for parity checking
struct precomputed_parity
{
  static constexpr size_t LUTSIZE = pow(2,WORDSIZEBIT);
  using LutType = std::array<short,LUTSIZE>;
  static LutType LUT;

  static void InitializeLUT()
  {
    for( size_t idx = 0; idx < std::tuple_size<LutType>::value; idx++ )
    {
      LUT.at(idx) = ParityNaive(idx);
    }
  }
};

template<size_t wordIndex, typename T>
struct ParityChecker
{
  static short check( T x )
  {
    return ParityChecker<wordIndex-1,T>::check(x)^
      ParityChecker<1,T>::check(x>>(wordIndex-1)*WORDSIZEBIT);
  }
};

template<typename T>
struct ParityChecker<1,T>
{
  static short check( T x )
  {
    return precomputed_parity::LUT[x&WORDMASK];
  }
};

//Third solution : Fast Lookup table based parity
template<typename T>
short ParityFastLUT( T x )
{
  static_assert( sizeof(T)%WORDSIZEBYTE == 0,
    "ParityFastLUT not available for that type" );
  return ParityChecker<sizeof(T)/WORDSIZEBYTE,T>::check(x);
}
