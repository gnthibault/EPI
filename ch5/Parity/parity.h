
//STL
#include <array>
#include <cmath>

#define WORDSIZEBYTE 2
#define WORDMASK 0xFFFF
#define WORDSIZEBIT WORDSIZEBYTE*8

//First solution : naive test for all bits : not even robust for signed integer
//because right shift produces 1-padding at the left
//Complexity is O(n) with n the number of bits in the type
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
//Complexity O(n) with n the number of bits in the type, in the worst case
//Complexity is O(k) with k the number of 1-valued bits in the word when k>=1
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

//Recursive fetching of parity for each 16 word that compose the type
template<size_t wordIndex, typename T>
struct ParityChecker
{
  static short check( T x )
  {
    return ParityChecker<wordIndex-1,T>::check(x)^
      ParityChecker<1,T>::check(x>>((wordIndex-1)*WORDSIZEBIT));
  }
};
//End of recursion: get the last 16 bit word that compose the type
template<typename T>
struct ParityChecker<1,T>
{
  static short check( T x )
  {
    return precomputed_parity::LUT[x&WORDMASK];
  }
};

//Third solution : Fast Lookup table based parity
//Complexity is O(n/L) with n the number of bits in the type, and L the number
//of bits that can be addressed using the lookup table. ie, if lookup table
//is large enough, complexity is O(1).
template<typename T>
short ParityFastLUT( T x )
{
  static_assert( sizeof(T)%WORDSIZEBYTE == 0,
    "ParityFastLUT not available for that type" );
  return ParityChecker<sizeof(T)/WORDSIZEBYTE,T>::check(x);
}

//Recursive XOR based parity checking between two halves of the current bit set
template<size_t nbStep, typename T>
struct XorParityChecker
{
  static short check( T x )
  {
    //we xor the first half of the first 2^nbStep bits with the second half
    constexpr int shift = std::pow(2,nbStep-1);
    return XorParityChecker<nbStep-1,T>::check(x^(x>>shift));
  }
};
//End of recursion: extract the very last bit
template<typename T>
struct XorParityChecker<0,T>
{
  static short check( T x )
  {
    return x & 0x1;
  }
};

//Fourth solution : Xor based parity
//Complexity is O(log(n)) with n the number of bits in the type
template<typename T>
short ParityXorBased( T x )
{
  constexpr size_t nbStep = std::log2(8*sizeof(T));
  return XorParityChecker<nbStep,T>::check(x);
}
