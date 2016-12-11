//STL
#include <iostream>

//Local
#include "BinaryTree.h"

//Compile using g++ ./main.cpp -std=c++14 -o ./test
int main( int argc, char* argv[] )
{
  BinaryTree<int64_t> bst;
  bst.Insert( 30 );
  bst.Insert( 10 );
  bst.Insert( -15 );
  bst.Insert( 30 );
  bst.Insert( 0 );
  bst.InOrderTraversal();

  std::cout <<"Mokay"<<std::endl;
  return EXIT_SUCCESS;
}
