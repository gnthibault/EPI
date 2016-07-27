

//First solution : naive test for all values
template<typename T>
short ParityNaive( T x )
{
  short result = 0;
  while(x)
  {
    result += ( x & 1 );
    x >>= 1;
  }
  return result % 2;
}
