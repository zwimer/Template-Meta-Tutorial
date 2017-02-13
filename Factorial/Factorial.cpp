/* Compiled with:
	g++ Factorial.cpp -Ofast -o Factorial.out
*/


#include <iostream>

// Template Meta, recursive function
template <unsigned int N> struct _Factorial {
	enum { value = N * _Factorial<N - 1>::value };
};

//Base case
template <> struct _Factorial<0> {
	enum { value = 1 };
};


// Factorial Wrapper
#define factorial(x) _Factorial<x>::value


//Main function
int main() {

	//Print out factorial examples
	std::cout << "Factorial(0) = " << factorial(0) << std::endl;
	std::cout << "Factorial(1) = " << factorial(1) << std::endl;
	std::cout << "Factorial(4) = " << factorial(4) << std::endl;
	std::cout << "Factorial(8) = " << factorial(8) << std::endl;

	//Success
	return 0;
}
