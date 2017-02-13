/* Compiled with:
	g++ FullTemplateSpec.cpp -Ofast -o FullTemplateSpec.out
*/

#include <iostream>


//General template
template <unsigned int N> struct _Factorial {
	enum { value = N * _Factorial<N - 1>::value };
};

//Note that here we have template <>
//This is FULL template specialization
//We then specify what arguments in the class name
template <> struct _Factorial<0> {
	enum { value = 1 };
};


// Factorial Wrapper
#define factorial(x) _Factorial<x>::value


//Main function
int main() {

	//Print out factorial examples
	std::cout << "Factorial(8) = " << factorial(8) << std::endl;

	//Success
	return 0;
}
