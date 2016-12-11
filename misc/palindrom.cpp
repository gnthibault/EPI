#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  int num = 0;

  std::cout << "Please write a number" << std::endl;
  std::cin >> num;

  //Get the total number of digits in base 10
  int maxExponent = 1;
  int rem = num;
  while( rem >= 10 )
  {
    rem = rem / 10;
    maxExponent*=10;
  }

  //Test if it is a palindrom
  int n = num;
  bool isPal = true;

  while(maxExponent>0)
  {
    int firstDig = n%10;
    int lastDig = n / maxExponent;

    isPal &= firstDig == lastDig;

    //Remove last digit
    n = n-lastDig*maxExponent;
    //Remove first digit
    n = (n-lastDig) / 10;

    maxExponent/=100;
  }

  if( isPal )
  {
    std::cout << "your number is a pal : "<<num<<std::endl;
  }else
  {
    std::cout << "your number is NOT a pal : "<<num<<std::endl;
  }
  return EXIT_SUCCESS;
}
