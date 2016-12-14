//STL
#include <iostream>

//Local
#include "BinaryTree.h"

//Compile using g++ ./main.cpp -std=c++14 -o ./test
int main( int argc, char* argv[] )
{
  BinaryTree<int64_t> bst;

  for( auto i : {30,0,10,-15,1,29})
    bst.Insert( i );
  bst.InOrderTraversal();

  std::cout <<"Mokay, now deleting "<<std::endl;
  for( auto i : {30,0,10,-15,1,29})
    bst.Delete(i);
  std::cout << "Result after deletion is (should be blank): "<<std::endl;
  bst.InOrderTraversal();
  return EXIT_SUCCESS;
}
