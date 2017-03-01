/* Compiled with:
	g++ Tuple.cpp -o Tuple.out
*/

#include <iostream>

//Macro wrapper
#define isPtr(T) ((bool) IsPointer<T>::result)

//Simple Tuple class
template <class T, class U> struct Tuple {
    typedef T Head;
    typedef U Tail;
};

//Declare a CopyTuple class
template <class T> struct CopyTuple;

//Add a template to this template specalization
template<> template <class T, class U>
struct CopyTuple< Tuple<T, U> > {
	typedef Tuple<T, U> result;
};


//Main function
int main() {

	//Create a tuple of an int and char
	typedef Tuple<int, char> A;

	//Copy A to B
	typedef CopyTuple< A >::result B;

	//Compare A and B
	std::cout << (typename A::Tail) 'A' << " = " << (typename B::Tail) 'A' << std::endl;
	std::cout << (typename A::Head) 'A' << " = " << (typename B::Head) 'A' << std::endl;

	//Success
	return 0;
}
