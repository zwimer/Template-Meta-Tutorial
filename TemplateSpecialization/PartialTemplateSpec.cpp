/* Compiled with:
	g++ PartialTemplateSpec.cpp -o PartialTemplateSpec.out
*/

#include <iostream>
#include <climits>

// Template Meta
template <int N, int N2> struct Division {
	enum { value = N / N2 };
};


//Note that here we have only one int in our template
//This is partial template specialization.
//We then specify what the arguments are below
template <int N> struct Division<N, 0> {
	enum { value = INT_MAX };
};


//Main function
int main() {

	//Test division
	std::cout << "4/2 = " << Division<4,2>::value << std::endl;
	std::cout << "4/0 = " << Division<4,0>::value << std::endl;

	//Success
	return 0;
}
