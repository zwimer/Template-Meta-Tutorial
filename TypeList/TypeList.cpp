/* Compiled with:
	g++ TypeList.cpp -o TypeList.cpp
*/

#include <iostream>

//A class that denotes the end of a TL
class NullType {};

// A simple Type List
template <class T, class U> struct Typelist {
	typedef T Head;
	typedef U Tail; 
};


/* Note: The following is for C++98.
 * There is a better way to do this with C++11 !
 * With variatic arguments, we will be able to
 * define a single function that does the job
 * of all of these macros! C++11 also allows for
 * default template arguments!
 */

// The C++98 Method ( C++11 is MUCH better for this )
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
// ...
// ...
// ...

// In C++11, none of this is needed, you can make a struct do it for you


//Main function
int main() {

	//Create a typelist of int and char
	typedef TYPELIST_2(int, char) TL;

	//Print out 'A' as an int and a char
	std::cout << (typename TL::Head) 'A' << std::endl;
	std::cout << (typename TL::Tail::Head) 'A' << std::endl;

	//Success
	return 0;
}
