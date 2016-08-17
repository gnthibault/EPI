//STL
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <vector>

//Boost
#include <boost/iterator/zip_iterator.hpp>

template<typename T>
void SortCheck( const std::vector<T>& in )
{
  if( in.size() <= 1 ) // vector of size <= 1 are always sorted
    return;

  auto diffBegin = boost::make_zip_iterator(
    boost::make_tuple( in.cbegin(), in.cbegin()+1 ) );
  auto diffEnd = boost::make_zip_iterator(
    boost::make_tuple( in.cend()-1, in.cend() ) );

  assert(
    std::accumulate( diffBegin, diffEnd, true,
      [](bool acc, auto diff) -> bool {
        return acc && (boost::get<0>(diff) <= boost::get<1>(diff));
      })
  );
}
