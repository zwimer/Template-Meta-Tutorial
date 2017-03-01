/* Compiled with:
	g++ BasicTypeList.cpp -o BasicTypeList.cpp
*/

#include <iostream>


// A simple Type List
template <class T, class U> struct Typelist {
	typedef T Head;
	typedef U Tail; 
};

//Main function
int main() {

	//Create a TL with a char and an int
	typedef Typelist<char, int> TL;

	//Print 'A' as a character and number
	std::cout << (typename TL::Head) 'A' << std::endl;
	std::cout << (typename TL::Tail) 'A' << std::endl;

	//Success
	return 0;
}
