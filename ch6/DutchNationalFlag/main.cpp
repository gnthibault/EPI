//Local
#include "Partition.h"
#include "../../Utility/SortCheck.h"

//STL
#include <cstdlib>


//We challenge the template test functor "Demo" over the
//cartesian product of the type sets T0,T1,T2
return TestImp<Demo>(T0(),T1(),T2()) ? EXIT_SUCCESS : -1;

//Compile using g++ ./main.cpp -std=c++14 -o ./test
int main( int argc, char* argv[])
{
  //Starting point of the random distribution
  using T0 = std::tuple<IntType<-10000>,IntType<-100>,
    IntType<-1>,IntType<0>,IntType<100>,IntType<10000>>;
  using T2 = std::tuple<IntType<-100>,IntType<100>,
    IntType<-1>,IntType<1>,IntType<0>>;

  //Initialize a vector with random values
  std::vector<int64_t> v(16);

  // Filling vector with random values
  std::random_device rnd_device;
  std::mt19937 mersenne_twister(rnd_device());
  std::uniform_int_distribution<int64_t> dist(1, 52);
  auto gen = std::bind(dist, mersenne_twister);
  std::generate(begin(v), end(v), gen);

  //Check if sorted
  SortCheck( v );

  return EXIT_SUCCESS;
}
