/* Compiled with:
	g++ TL_Append.cpp -o TL_Append.out
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


// Below assumes no errors. If you don't like this, feel free
// to throw in some of the static asserts you learned below!

//Declare the TypeAt struct
// U is what is being appended to the typelist T
// If T is Null and U is Null, return Null
// If T is Null and U is not, return a typelist containing only U
// If T is Null and U is a typelist, then return U
// If T is not null, append T::Head to Append<T::Tail, U>
template<class T, class U> struct Append;

//Append Null to an empty list
template <> struct Append<NullType, NullType> {
	typedef NullType Result;
};

//Append U to an empty list
template <class U> struct Append<NullType, U> {
	typedef TYPELIST_1(U) result;
};

//Append a typelist to a null list
template <class T, class U> struct Append<NullType, Typelist<T, U> > {
	typedef Typelist<T, U> result;
};

// If T is not null, append T::Head to Append<T::Tail, U>
template<> template<class Head, class Tail, class U>
struct Append<Typelist<Head, Tail>, U> {
	typedef Typelist<Head, typename Append<Tail, U>::result> result;
};


//Main function
int main() {

	//Create a typelist of char
	typedef TYPELIST_1(char) T1;

	//Append an int to the end of T1
	typedef Append<T1, int>::result T2;

	//Print out 'A' as an int and a char
	std::cout << ( T2::Head ) 'A' << std::endl;
	std::cout << ( T2::Tail::Head ) 'A' << std::endl;

	//Success
	return 0;
}
